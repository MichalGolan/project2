#ifndef _COMPRESS_H
	#define _COMPRESS_H

#include "chessPosList.h"

#define LET_MASK 1 << 5
#define DIG_MASK 1 << 2

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);
/* E - this function get chessPos list, creates binary file with compressed information from the given list*/

void fillArrFromList(chessPosList* pos_list, BYTE* res); /*!!!!!!*/
/*fill BYTE array with compressed information from pos_list*/

void setBit(BYTE* dest, BYTE dest_mask, BYTE src, BYTE mask_src);
/*turn specific bit 1/0*/

BYTE makeBin(chessPos CP);
/*create a BYTE value with compressed information for chessPos*/

int getbyteSize(int bitSize);
/*return how many bytes needed to contain given number of bits*/

void checkFile(FILE* file);
/*check file opening failure */

int checkAndDisplayPathFromFile(char* file_name);
/* F - the function recive a file name of a file containing a compressed list of positions. return (-1,1,2,3) for whats in the list 
if the list contains a full board path, print board with the path*/

int checkList(chessPosList* lst);
/* check if a list is a legitimate knight path, if it is, checks if it covers all the board's locations*/

void makeListFromFile(FILE* file, unsigned short listSize, chessPosList* lst);
/*this function get file with compressed list of positions and create a list*/

void makeListFromArr(chessPosList* lst, BYTE* arr, unsigned short listSize, int byteSize); /*!!!!!!!*/
/* create a list of positions from a BYTE array that conatins a compressed list of positions */

void insertBinDataToList(BYTE CP, chessPosList* lst);
/*insert binary data to list*/

int extractbit(BYTE CP, BYTE mask);
/*uncompressed 3 bits according to given mask*/

int checkLegit(chessPosList* lst);
/*check if list contains only legitimate knight moves*/

int notNeighbor(chessPos curr, chessPos next);
/*check for two chess positions if they are a knight move away from each other*/


#endif 
