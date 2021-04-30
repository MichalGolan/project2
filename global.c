#include "global.h"

void fillChessPos(chessPos pos, int let, int dig)
{
	*(pos + LET) = let + 'A';
	*(pos + DIG) = dig + '1';
}

void checkAlloc(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Oh no! Memory allocation failed :(");
		exit(1);
	}
}