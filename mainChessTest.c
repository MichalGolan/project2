#define _CRT_SECURE_NO_WARNINGS
#include "ProjectMainFunctions.h"
/*
#define LET 0
#define DIG 1
#define SIZE 8 /*row and col size*/
/*#define TRUE 1
#define FALSE 0

typedef char chessPos[2];
typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;
*/

/* A */


/* B */

/*aronov michal*/
/*michal golan*/




void main()
{
	/*chessPos pos;
	chessPosArray square;
	fillchessPosArray(&square, 0, 0);
	printf("size %d\n", square.size);
	printChessPos(*(square.positions));
	printChessPos(*(square.positions + 1));*/

	chessPosArray*** testBoard;
	testBoard = validKnightMoves();

	testDisplay();


	//printChessPosArray(*(*(testBoard))+7); /*how to go to a square*/

}