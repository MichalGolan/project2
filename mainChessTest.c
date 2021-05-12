#define _CRT_SECURE_NO_WARNINGS
//#include "ProjectMainFunctions.h"

#include "global.h"
#include "ChessPossTree.h"
#include "chessPosList.h"

void printlist(chessPosList* lst);

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
	printlist(lst);

	printf("\n\npos 1:");
	printChessPos(path.root->position);

	//printChessPosArray(*(*(testBoard))+7); /*how to go to a square*/

}

void printlist(chessPosList* lst)
{
	int i = 1;
	chessPosCell* curr = lst->head;
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