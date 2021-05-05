
/*this module includes the globally needed definitions of the entire project
for all other modules to use*/

#ifndef GLOBAL_H
#define GLOBAL_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LET 0
#define DIG 1
#define SIZE 8 /*row and col size*/
#define TRUE 1
#define FALSE 0

typedef char chessPos[2];

void checkAlloc(void* ptr); /*the functions checks allocation memory failure*/

void fillChessPos(chessPos pos, int let, int dig);
/*the function puts data of chess position in the chessPos struct*/

void copyChessPos(chessPos src, chessPos dest);
/*the function copy one chessPos to another*/

#endif