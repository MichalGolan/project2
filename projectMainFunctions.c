#include "ProjectMainFunctions.h"

chessPosArray*** validKnightMoves()
{
	int i, j, k;
	chessPosArray** board = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
	for (k = 0; k < SIZE; k++)
	{
		board[k] = (chessPosArray*)malloc(SIZE * sizeof(chessPosArray));
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			fillchessPosArray(&board[i][j], i, j);

		}
	}
	return &board;
}

void display(chessPosList* lst)
{
	chessPosCell* ptr1, * ptr2;
	ptr1 = ptr2 = lst->head;

	while (ptr1 != NULL && ptr2 != NULL)
	{
		ptr2 = ptr1;

		while (ptr2->next != NULL)
		{
			if (isEqual(ptr1->position, ptr2->next->position))
			{
				removeCell(ptr2, lst);
			}
			else
			{
				ptr2 = ptr2->next;
			}
		}
		ptr1 = ptr1->next;
	}
	printBoardFromList(lst);
}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	chessPosArray*** movesMat;
	movesMat = validKnightMoves();

	stringArray stringTable[SIZE][SIZE];
	initializeStringTable(stringTable);

	pathTree treePath;
	treePath.root = findPathsRec(*startingPosition, movesMat, stringTable, '1', '1');


	return treePath;
}