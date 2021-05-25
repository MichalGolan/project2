#define _CRT_SECURE_NO_WARNINGS
//#include "ProjectMainFunctions.h"

#include "global.h"
#include "ChessPossTree.h"
#include "compress.h"

void printlist(chessPosCell* head);

void main()
{
	chessPosArray*** testBoard;
	testBoard = validKnightMoves();

	testDisplay();
	chessPos check;
	check[0] = 'C';
	check[1] = '3';

	pathTree path = findAllPossibleKnightPaths(check);
	
	chessPosList* lst = findKnightpathCoveringAllBoard(&path);
	printlist(lst->head);

	chessPosList pos_list = createNewList();
	saveListToBinFile("test.bin", &pos_list);


	printChessPos(path.root->position);
	freePathTree(path);
	freeChessPosArray(testBoard);
	freeList(lst);
}

void printlist(chessPosCell* head)
{
	int i = 1;
	chessPosCell* curr = head;
	if (curr == NULL)
	{
		printf("empty List, no full board path");
	}
	else
	{
		while (curr != NULL)
		{
			printf("move %d: ", i);
			printChessPos(curr->position);
			curr = curr->next;
			i++;
		}
	}
}