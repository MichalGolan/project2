#include "ChessPosList.h"

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


void removeCell(chessPosCell* deleteAfter, chessPosList* lst)
{
	if (lst->tail == deleteAfter->next)
	{
		lst->tail = deleteAfter;
	}
	chessPosCell* tmp = deleteAfter->next->next;
	free(deleteAfter->next);
	deleteAfter->next = tmp;
}

chessPosCell* createNewCell(chessPos data, chessPosCell* next)
{
	chessPosCell* newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
	*(newCell->position) = data[LET];
	*(newCell->position + 1) = data[DIG];
	newCell->next = next;
	return newCell;
}

void insertDatatoEndList(chessPosList* lst, int letter, int digit)
{
	chessPos newPos;
	chessPosCell* newTail;
	fillChessPos(newPos, letter, digit);
	newTail = createNewCell(newPos, NULL);

	insertCellToEndList(lst, newTail);
}

void insertCellToEndList(chessPosList* lst, chessPosCell* newCell)
{
	if (lst->head == NULL)
	{
		lst->head = lst->tail = newCell;
	}
	else
	{
		lst->tail->next = newCell;
		lst->tail = newCell;
	}
}

void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

chessPosList createNewList()
{
	chessPosList lst;
	makeEmptyList(&lst);

	chessPos data1 = { 'C','5' };
	chessPos data2 = { 'A','4' };
	chessPos data3 = { 'B','3' };
	chessPos data4 = { 'D','1' };
	chessPos data5 = { 'E','3' };


	insertCellToEndList(&lst, createNewCell(data1, NULL));
	insertCellToEndList(&lst, createNewCell(data2, NULL));
	insertCellToEndList(&lst, createNewCell(data3, NULL));
	insertCellToEndList(&lst, createNewCell(data4, NULL));
	insertCellToEndList(&lst, createNewCell(data5, NULL));

	return lst;
	printf("end");
}

void fillByList(int board[][SIZE], chessPosList* lst)
{
	int i = 1;
	int row, col;
	chessPosCell* curr = lst->head;

	while (curr != NULL)
	{
		row = curr->position[LET] - 'A';
		col = curr->position[DIG] - '1';

		board[row][col] = i;
		i++;
		curr = curr->next;
	}
}

void printBoardFromList(chessPosList* lst)
{
	int i, j, k;
	int board[SIZE][SIZE] = { 0 };
	fillByList(board, lst);
	
	printf("\n     ");
	for (k = 0; k < SIZE; k++)
	{
		printf("|  %d  ", k+1);
	}
	printf("| \n -----");
	for (k = 0; k < SIZE; k++)
	{
		printf("------");
	}
	printf("\n");

	for (i = 0; i < SIZE; i++)
	{
		printf("%4c |", i + 'A');
		for (j = 0; j < SIZE; j++)
		{
			if (board[i][j] == 0)
			{
				printf("     |");
			}
			else
			{
				printf("  %d  |", board[i][j]);
			}

		}
		printf(" \n -----");
		for (k = 0; k < SIZE; k++)
		{
			printf("------");
		}
		printf("\n");
	}
	printf("\n");
}

/*check if two chessPos are equals*/
int isEqual(chessPos pos1, chessPos pos2)
{
	int res = FALSE;
	if (pos1[LET] == pos2[LET] && pos1[DIG] == pos2[DIG])
	{
		res = TRUE;
	}
	return res;
}

void testDisplay()
{
	chessPosList lst = createNewList();
	display(&lst);
}

void insertDataToList(chessPosList* lst, chessPos pos)
{
	chessPosCell* newCell = createNewCell(pos, NULL);
	insertCellToStartList(lst, newCell);
}

void insertCellToStartList(chessPosList* lst, chessPosCell* newCell)
{
	if (lst->head == NULL)
	{
		lst->head = lst->tail = newCell;
	}
	else
	{
		newCell->next = lst->head;
		lst->head = newCell;
	}
}

void freeList(chessPosList* lst)
{
	chessPosCell* curr = lst->head, * next;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}


short int getListSize(chessPosList* pos_list)
{
	chessPosCell* curr = pos_list->head;
	short int len = 0;

	while (curr != NULL)
	{
		curr = curr->next;
		len++;
	}
	return len;
}
