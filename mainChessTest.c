#define _CRT_SECURE_NO_WARNINGS
#include "ProjectMainFunctions.h"

#include "global.h"


void main()
{
	chessPosArray*** testBoard;
	testBoard = validKnightMoves();

	testDisplay();


	//printChessPosArray(*(*(testBoard))+7); /*how to go to a square*/

}