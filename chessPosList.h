#ifndef ChessPosList_H_
#define ChessPosList_H_

#include "global.h"


typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


void removeCell(chessPosCell* deleteAfter, chessPosList* lst);
/*the function removes chessPosCell after the one that is given*/

chessPosCell* createNewCell(chessPos data, chessPosCell* next);
/*function creates a new chessPosCell given data*/

void insertDatatoEndList(chessPosList* lst, int letter, int digit);
/*this function receives a letter, a digit and a list and inserts a new chessPosCell
to the end of the list accordingly*/

void insertCellToEndList(chessPosList* lst, chessPosCell* newCell);
/*function puts a given chessPosCell at the end of the list*/

void makeEmptyList(chessPosList* lst);
/*function creates an empty chessPosList*/

chessPosList createNewList();
/*this is a debugging function - creates a new list with data*/

int isEqual(chessPos pos1, chessPos pos2);
/*this function checks and returns
TRUE - the two chess positions are equal
FALSE - other wise*/

void printBoardFromList(chessPosList* lst);
/*this function receives a list of chess positions and prints a board accordingly*/

void fillByList(int board[][SIZE], chessPosList* lst);
/*this function receives a two dimensional array the size of a chess board,
and fills it according to the list*/

void testDisplay();
/*this is a debugging function to check that display is working correctly*/

#endif
