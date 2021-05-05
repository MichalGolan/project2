#define _CRT_SECURE_NO_WARNINGS
//#include "ProjectMainFunctions.h"

#include "global.h"
#include "ChessPossTree.h"
#include "chessPosList.h"

void main()
{
	chessPosArray*** testBoard;
	testBoard = validKnightMoves();

	testDisplay();
	chessPos check;
	check[0] = 0;
	check[1] = 0;


	pathTree path = findAllPossibleKnightPaths(check);
	int i;

	printf("pos 1:");
	printChessPos(path.root->position);

	//printChessPosArray(*(*(testBoard))+7); /*how to go to a square*/

}