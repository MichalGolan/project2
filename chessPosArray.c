#include "ChessPosArray.h"

chessPosArray*** validKnightMoves()
{
	int i, j, k;
	chessPosArray*** pBoard = (chessPosArray***)malloc(sizeof(chessPosArray**));
	checkAlloc(pBoard);
	chessPosArray** board = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
	checkAlloc(board);

	for (k = 0; k < SIZE; k++)
	{
		board[k] = (chessPosArray*)malloc(SIZE * sizeof(chessPosArray));
		checkAlloc(board[k]);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fillchessPosArray(&board[i][j], i, j);
		}
	}
	*pBoard = board;
	return pBoard;
}

void freeChessPosArray(chessPosArray*** pBoard)
{
	int i, j;
	chessPosArray** board = *pBoard;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			free((board[i][j]).positions);
		}
		free(board[i]);
	}
	free(board);
	free(pBoard);
}

/* this function get locatin in board [i][j] and: count how many moves knight can do and where + fill chessPosArray with relevent locations*/
void fillchessPosArray(chessPosArray* square, int i, int j)
{
	int size = 0;
	chessPos* array = (chessPos*)malloc(sizeof(chessPos) * MAXPOS);
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

	if (size < MAXPOS)
	{
		array = (chessPos*)realloc(array, sizeof(chessPos) * size);
	}
	square->size = size;
	square->positions = array;
}