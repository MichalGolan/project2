#ifndef _MENU_H
	#define _MENU_H

#include "compress.h"
#include "ChessPossTree.h"

#define isValMove(c, z) ( ((c) - (z)) >= 0 && ((c) - (z)) < SIZE)
#define invalid_choice 1
#define invalid_Input 2
#define no_location_given 3


void menu();

void printMenu();

void getLocation(chessPos location);

void printError(int error_index);

void optionTwo(chessPos location, pathTree* path_tree);

void optionThree(chessPos location, pathTree* path_tree, chessPosList* lst);


#endif 
