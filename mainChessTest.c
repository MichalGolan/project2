#define _CRT_SECURE_NO_WARNINGS
//#include "ProjectMainFunctions.h"

#include "global.h"
#include "ChessPossTree.h"
#include "compress.h"


void main()
{
/*	chessPosArray*** testBoard;
	testBoard = validKnightMoves();

	testDisplay();
	chessPos check;
	check[0] = 'C';
	check[1] = '3';

	pathTree path = findAllPossibleKnightPaths(check);
	
	chessPosList* lst;
	lst = findKnightpathCoveringAllBoard(&path);
	printlist(lst);
	*/
	chessPosList pos_list = createNewList();
	saveListToBinFile("test.bin", &pos_list);
	checkAndDisplayPathFromFile("test.bin");
	/*

	printChessPos(path.root->position);
	freePathTree(path);
	freeChessPosArray(testBoard);
	freeList(lst);*/
}


