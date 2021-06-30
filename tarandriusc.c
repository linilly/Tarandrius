// tarandriusc

//included libraries
#include <stdio.h>
#include <stdlib.h>
//defintions
#define fen "2r5/1b2r1k1/1p1q2pp/p1pp1p2/P2PnN1P/3QPNP1/1P3PK1/2R4R b - - 1 27"

//strucutres
struct pieceHolder {signed pieceType: 4;};
struct HashKEY_Eval {unsigned KEY: 29; int eval;};
struct tagInfo {unsigned turnColour: 1; unsigned castlingRignts: 4; unsigned char sLeft;};
struct Piece_Square {signed piece: 4; unsigned char square; struct Piece_Square *next;};
struct smartBoard {struct tagInfo tag; struct Piece_Square *pieceBoardHead[3];};

//library functions
void strFlush(unsigned char *input, unsigned char flushLen);
void strFlush(unsigned char *input, unsigned char flushLen)
{
    unsigned char ctr;
    for(ctr=0; ctr<flushLen; ctr++) input[ctr]=0;
}

/*unsigned char simplePower(unsigned char base, char expo);
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

unsigned char numberExtract(char *FEN);
unsigned char numberExtract(char *FEN)
{
    unsigned char ctr, lenCt = 0, number = 0, placeholder[3];
    strFlush(placeholder, 3);

    while (*++FEN > 47 && *FEN < 58)
        placeholder[lenCt++] = (*FEN - 48);
    for (ctr = 0; ctr < lenCt; ctr++)
        number += placeholder[ctr] * simplePower(10, lenCt - ctr - 1);
    FEN++;
    return number;
}*/

//functions
//propped stage (*Don't touch*)
void inBoard_set(struct pieceHolder *inBoard);
void inBoard_set(struct pieceHolder *inBoard)
{
    unsigned char ctr;
    for (ctr = 0; ctr < 120; ctr++)
        inBoard[ctr].pieceType = 0;
}

void inBoardPrint(struct pieceHolder *inBoard);
void inBoardPrint(struct pieceHolder *inBoard)
{
    unsigned char ctr;
    for (ctr = 0; ctr < 120; ctr++)
    {if (ctr % 10 == 0) printf("\n\n"); printf("%d\t", inBoard[ctr].pieceType);}
}

void FENparse(char *FEN, struct pieceHolder *inBoard)
{
    unsigned char ctr;
    for (ctr = 21; ctr < 99; ctr++)
        if (*FEN > 48 && *FEN < 57) ctr = ctr + *FEN++ - 49;
        else switch (*FEN++)
        {
            case '/': ctr++;                       break;
            case 'P': inBoard[ctr].pieceType =  6; break;
            case 'p': inBoard[ctr].pieceType = -6; break;
            case 'R': inBoard[ctr].pieceType =  3; break;
            case 'r': inBoard[ctr].pieceType = -3; break;
            case 'B': inBoard[ctr].pieceType =  4; break;
            case 'b': inBoard[ctr].pieceType = -4; break;
            case 'N': inBoard[ctr].pieceType =  5; break;
            case 'n': inBoard[ctr].pieceType = -5; break;
            case 'Q': inBoard[ctr].pieceType =  2; break;
            case 'q': inBoard[ctr].pieceType = -2; break;
            case 'K': inBoard[ctr].pieceType =  1; break;
            case 'k': inBoard[ctr].pieceType = -1; break;
        }
// Turn colour
    if (*++FEN == 'w') inBoard[0].pieceType = 0;
    else               inBoard[0].pieceType = 1;
    FEN++;
// Castling rights
    if (*++FEN == '-') FEN++;
    if (*FEN == 'K') {inBoard[1].pieceType += 8; FEN++;}
    if (*FEN == 'Q') {inBoard[1].pieceType += 2; FEN++;}
    if (*FEN == 'k') {inBoard[1].pieceType += 4; FEN++;}
    if (*FEN == 'q') {inBoard[1].pieceType += 1; FEN++;}
// En passant
    if (*++FEN == '-') FEN--;
    else if (*++FEN == '6') inBoard[*--FEN - 56].pieceType = -7;
    else                    inBoard[*--FEN - 26].pieceType =  7;
    FEN++; FEN++;
// R-mob score
    /*ctr = numberExtract(FEN);
    inBoard[2].pieceType = ctr / 15;
    inBoard[3].pieceType = ctr % 15;
    while (*++FEN > 47 && *FEN < 58);*/
// Movesleft
    //ctr = numberExtract(FEN);
    inBoard[4].pieceType = ctr / 15;
    inBoard[5].pieceType = ctr % 15;
    while (*++FEN > 47 && *FEN < 58);
// Movecount
    //printf("{%c}", *++FEN);
}

// smart set
struct smartBoard smartBoard_init(struct pieceHolder *inBoard, struct smartBoard position);
struct smartBoard smartBoard_init(struct pieceHolder *inBoard, struct smartBoard position)
{
    unsigned char ctr, ptrctr;
    struct Piece_Square *ptr[3];
    for (ptrctr = 0; ptrctr < 3; ptrctr++)
    {
        ptr[ptrctr] = (struct Piece_Square*)malloc(sizeof(struct Piece_Square));
        ptr[ptrctr]->next = position.pieceBoardHead[ptrctr];
        position.pieceBoardHead[ptrctr] = ptr[ptrctr];
        position.pieceBoardHead[ptrctr]->next = NULL;
    }

    for (ctr = 21; ctr < 99; ctr++)
        if (inBoard[ctr].pieceType != 0)
        {
            struct Piece_Square *Lptr[3];
            for (ptrctr = 0; ptrctr < 3; ptrctr++)
            {
                Lptr[ptrctr] = (struct Piece_Square*)malloc(sizeof(struct Piece_Square));
                Lptr[ptrctr]->piece = inBoard[ctr].pieceType;
                Lptr[ptrctr]->square = ctr;
                if ((ptrctr == 0 && inBoard[ctr].pieceType < 0) || (ptrctr == 1 && inBoard[ctr].pieceType > 0)) continue;
                struct Piece_Square *current;
                current = position.pieceBoardHead[ptrctr];
                while (current->next != NULL) current = current->next;
                current->next = Lptr[ptrctr];
                Lptr[ptrctr]->next = NULL;
            }
        }
    return position;
}

//Movegen functions
void kingGen(unsigned char square);
void kingGen(unsigned char square)
{
    ;
}
void queenGen(unsigned char square);
void queenGen(unsigned char square)
{
    ;
}
void rookGen(unsigned char square);
void rookGen(unsigned char square)
{
    ;
}
void bishopGen(unsigned char square);
void bishopGen(unsigned char square)
{
    ;
}
void knightGen(unsigned char square);
void knightGen(unsigned char square)
{
    ;
}
void pawnGen(unsigned char square);
void pawnGen(unsigned char square)
{
    ;
}

void legalGen(unsigned char piece, unsigned char square);
void legalGen(unsigned char piece, unsigned char square)
{
    switch (piece)
    {
        case  1: kingGen(square);   break;
        case  2: queenGen(square);  break;
        case  3: rookGen(square);   break;
        case  4: bishopGen(square); break;
        case  5: knightGen(square); break;
        case  6: pawnGen(square);   break;
    };
}

void squareAttackedGen(struct smartBoard position);
void squareAttackedGen(struct smartBoard position)
{
    struct Piece_Square *current;
    current = position.pieceBoardHead[position.tag.turnColour];
    while (current->next != NULL)
    {
        legalGen((unsigned char)current->piece, current->square);
        current = current->next;
    }
}

//main()
/*int main()
{
    unsigned char ctr;
    struct pieceHolder inBoard[120];
    inBoard_set(inBoard);
    FENparse(fen, inBoard);
    inBoardPrint(inBoard);
    // propped_init for debugging purposes /debug
    struct smartBoard position;
    position = smartBoard_init(inBoard, position);
    // print /debug
    for (ctr = 0; ctr < 3; ctr++)
        while (position.pieceBoardHead[ctr]->next != NULL)
        {
            position.pieceBoardHead[ctr] = position.pieceBoardHead[ctr]->next;
            printf("\n%u: %d, %d", ctr, position.pieceBoardHead[ctr]->square, position.pieceBoardHead[ctr]->piece);
        }
    squareAttackedGen(position);

    return 0;
}
*/
