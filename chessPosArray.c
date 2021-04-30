#include "ChessPosArray.h"

void printChessPos(chessPos pos)
{
	printf("array: LET %c, DIG %c\n", pos[LET], pos[DIG]);
}

void printChessPosArray(chessPosArray* square)
{
	unsigned int i;
	for (i = 0; i < (square->size); i++)
	{
		printChessPos(*(square->positions + i));
	}
}

/* this function get locatin in board [i][j] and: count how many moves knight can do and where + fill chessPosArray with relevent locations*/
void fillchessPosArray(chessPosArray* square, int i, int j)
{
	int size = 0;
	chessPos* array = (chessPos*)malloc(sizeof(chessPos) * SIZE);
	checkAlloc(array);

	if (i + 2 < SIZE && j + 1 < SIZE) /* check if 2 to the right and 1 down is in table*/
	{
		fillChessPos(array[size], i + 2, j + 1);
		size++;
	}
	if (i + 2 < SIZE && j - 1 >= 0) /* check if 2 to the right and 1 up is in table*/
	{
		fillChessPos(array[size], i + 2, j - 1);
		size++;
	}
	if (i - 2 >= 0 && j + 1 < SIZE) /* check if 2 to the left and 1 down is in table*/
	{
		fillChessPos(array[size], i - 2, j + 1);
		size++;
	}
	if (i - 2 >= 0 && j - 1 >= 0) /* check if 2 to the left and 1 up is in table*/
	{
		fillChessPos(array[size], i - 2, j - 1);
		size++;
	}
	if (i + 1 < SIZE && j + 2 < SIZE) /* check if 1 to the right and 2 down is in table*/
	{
		fillChessPos(array[size], i + 1, j + 2);
		size++;
	}
	if (i + 1 < SIZE && j - 2 >= 0) /* check if 1 to the right and 2 up is in table*/
	{
		fillChessPos(array[size], i + 1, j - 2);
		size++;
	}
	if (i - 1 >= 0 && j + 2 < SIZE) /* check if 1 to the left and 2 down is in table*/
	{
		fillChessPos(array[size], i - 1, j + 2);
		size++;
	}
	if (i - 1 >= 0 && j - 2 >= 0) /* check if 1 to the left and 2 up is in table*/
	{
		fillChessPos(array[size], i - 1, j - 2);
		size++;
	}

	if (size < SIZE)
	{
		array = (chessPos*)realloc(array, sizeof(chessPos) * size);
	}
	square->size = size;
	square->positions = array;
}