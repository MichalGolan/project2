
#ifndef CHESSPOSARRAY_H
#define CHESSPOSARRAY_H

#include "global.h"

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

void fillchessPosArray(chessPosArray* square, int i, int j);
/*the function receives a pointer to a struct of ChessPosArray and fills its ChessPos array
with the correct moves to which the kngiht can go from it, accordint to given (i,j) = (letter, digit)*/

void printChessPos(chessPos pos);
/*the function prints a single chess position*/

void printChessPosArray(chessPosArray* square);
/*the function prints an array of chess positions*/

#endif
