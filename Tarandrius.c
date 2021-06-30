// tarandriusc// Tarandrius 0.0.0 -dev

// #
// #include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
// #define
#define null '\0'

// struct
struct Tag {unsigned turnColour: 1; unsigned castlingRignts: 4; unsigned char sLeft;};
struct PieceSquare {signed piece: 4; unsigned char square; struct Piece_Square *next;};
struct SmartBoard {struct Tag tag; struct PieceSquare *head[3];};
struct LegalMoves
{
    //xRay
    //SoftLegal
    //StrictLegal
    int rMob;
    //overPrune
};
struct CompleteBoard
{
    unsigned _hash: 15;
    struct SmartBoard postion;
    struct LegalMoves mobility;
    int eval;
};

// functions

// library functions

unsigned char simplePower(unsigned char base, char expo);
unsigned char simplePower(unsigned char base, char expo)
{
    unsigned product=1;
    while(expo!=0)
    {
        if(expo>0) {product*=base; expo--;}
        else       {product/=base; expo++;}
    }
    return product;
}

unsigned char whole_numberExtract(char *FEN);
unsigned char whole_numberExtract(char *FEN)
{
    unsigned char ctr, lenCt=0, number=0, placeholder[3];
    memset(placeholder, 0, 3);

    while(*++FEN>47&&*FEN<58)
        placeholder[lenCt++]=(*FEN-48);
    for(ctr=0; ctr<lenCt; ctr++)
        number+=placeholder[ctr]*simplePower(10, lenCt-ctr-1);
    return number;
}

char *wordExtract(char *input);
char *wordExtract(char *input)
{
    unsigned char ctr=0;
    char sch;
    memset(input, 0, 255);
    sch=getchar();
    while((sch==32)||(sch=='\t')) sch=getchar();
    if(sch==10) return input;
    while ((sch!=32)&&(sch!='\t'))
    {
        if(sch==10) {ungetc(sch, stdin); break;}
        // modify
        input[ctr++]=sch;
        sch=getchar();
    }
    return input;
}

//functions

// uci support

// /interrupts
void getsInput();
void getsInput()
{
    char input[16];
    FILE *fp;
    while (1)
    {
        fp = fopen("ComsC.txt", "a");
        strcpy(input, wordExtract(input));
        fputs(input, fp);
        if (input[0] == 0) fputc(10, fp);
        else fputc(32, fp);
        fclose(fp);
    }
}

void interrupt();
void interrupt()
{
    pthread_t ComsH;
    pthread_create(&ComsH, NULL, (void *)getsInput, NULL);
    char commands[511];
    FILE *fp;
    while (1)
    {
        fp = fopen("ComsC.txt", "r+");
        while (1)
        {
            memset(commands, 0, 511);
            commands[0] = fgetc(fp);
            if (commands[0] == -1) break;
            fgets(&commands[1], 511, fp);
            if (strcmp(commands, "isready \n") == 0) exit(0);
            if (strcmp(commands, "quit \n") == 0) exit(0);
            if (strcmp(commands, "stop\n") == 0) exit(0);
        }
        fclose(fp);
    }
}

//uci
void UCI_uci();
void UCI_uci()
{
    char input[255];
    while (strcmp("uci", wordExtract(input)) != 0);

    puts("id name Tarandrius");
    puts("id author Linilly Z.");

    puts("option name Hash type spin default 131072 min 64");
    puts("option name Threads type spin default 176 min 4");
    puts("option name rMob type check");
    puts("option name Matrix type check");
    puts("option name NNUE type check");
    //puts("option name Contempt type spin default 18 min -50 max -50");
    puts("option name Ponder type check");
    puts("option name OwnBook type check");
    //puts("option name SyzygyPath type string");
    //puts("option name SyzygyCache type spin");

    puts("uciok");

    pthread_t interruptHandler;
    pthread_create(&interruptHandler, NULL, (void *)interrupt, NULL);
}

// board functions


// int main()
int main()
{
    UCI_uci();
    while (1);
    //struct CompleteBoard board;

    //if (strcmp("position", wordExtract(input))) --deactivate failsafe
    //board.postion = SmartBoard_init(board.postion);

    //
    return 0;
}
