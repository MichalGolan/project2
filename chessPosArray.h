
#ifndef CHESSPOSARRAY_H
#define CHESSPOSARRAY_H

#include "global.h"
#define MAXPOS 8 /*maximum possible moves*/

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

chessPosArray*** validKnightMoves();
/*A - the function returns a two-dimensional array,
where in every cell there is an array of chess positions to where a knight
can move from this cell*/

void fillchessPosArray(chessPosArray* square, int i, int j);
/*the function receives a pointer to a struct of ChessPosArray and fills its ChessPos array
with the correct moves to which the kngiht can go from it, accordint to given (i,j) = (letter, digit)*/

void freeChessPosArray(chessPosArray*** pBoard);
/*free chessPos array*/

#endif
