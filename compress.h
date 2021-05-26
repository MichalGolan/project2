#ifndef _COMPRESS_H
	#define _COMPRESS_H

#include "chessPosList.h"

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);
/* E - this function get chessPos list, creates binary file with compressed information from the given list*/

void fillArrFromList(chessPosList* pos_list, BYTE* res);
/*fill BYTE array with compressed information from pos_list*/

void setBit(BYTE* res, BYTE bin_CP, BYTE mask, int ind_byte, BYTE bit_mask, int* ind_bit);
/*turn specific bit 1/0*/

BYTE makeBin(chessPos CP);
/*create a BYTE value with compressed information for chessPos*/

int getbyteSize(int bitSize);
/*return how many bytes needed to contain given number of bits*/

void checkFile(FILE* file);
/*check file opening failure */

int checkAndDisplayPathFromFile(char* file_name);

int checkList(chessPosList* lst);

void makeListFromFile(FILE* file, unsigned short listSize, chessPosList* lst);

void makeListFromArr(chessPosList* lst, BYTE* arr, unsigned short listSize, int byteSize);

void insertBinDataToList(BYTE CP, chessPosList* lst);

int extractbit(BYTE CP, BYTE mask);

int checkLegit(chessPosList* lst);

int notNeighbor(chessPos curr, chessPos next);



#endif 
