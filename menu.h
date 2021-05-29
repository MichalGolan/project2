#ifndef _MENU_H
	#define _MENU_H

#include "compress.h"
#include "ChessPossTree.h"

#define isValMove(c, z) ( ((c) - (z)) >= 0 && ((c) - (z)) < SIZE)
#define invalid_choice 1
#define invalid_Input 2
#define no_location_given 3

void menu();
/* main switch for all the options in the menu */

void printMenu();
/* print menu */

void getLocation(chessPos location);
/*get chess possition from user*/

void printError(int error_index);
/*print errors by indexes*/

void optionTwo(chessPos location, pathTree* path_tree);
/*build a tree of all possible path from given location. if no location given, inform the user*/

chessPosList* optionThree(chessPos location, pathTree* path_tree, int* searchPath);
/*find a knight path that covers all the board from location. if no location given, inform the user*/

void optionFour(chessPos location, chessPosList* lst, pathTree* path_tree, int* searchPath);
/*get file name from user, print to a binary file a list if the list covers the entire board. otherwise, inform the user */

char* getFileName();
/* get file name from user */

void optionFive();
/* get a file name from user, the file contain a compressed list of positions.  print messages according to whats in the file 
if the list from the file contains a full board path, print board with the path */

void printCase(int fileRet);
/* print messages to user according to index */

void restart(int* searchPath, chessPosList* lst, pathTree* path_tree);

#endif 
