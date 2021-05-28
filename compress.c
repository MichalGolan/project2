#include "compress.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	unsigned short listSize = getListSize(pos_list);
	int byteSize = getbyteSize(listSize * 6);

	FILE* file = fopen(file_name, "wb");
	checkFile(file);

	fwrite(&listSize, sizeof(unsigned short), 1, file);

	BYTE* res = (BYTE*)calloc(byteSize, sizeof(BYTE));
	checkAlloc(res);

	fillArrFromList(pos_list, res);

	fwrite(res, sizeof(BYTE), byteSize, file);

	fclose(file);
	free(res);
}

void fillArrFromList(chessPosList* pos_list, BYTE* res)
{
	chessPosCell* curr = pos_list->head;
	chessPos CP;
	int ind_byte = 0, ind_bit=0, i;
	BYTE bin_CP, bit_mask = 1 << 7;

	while (curr != NULL)
	{
		copyChessPos(curr->position, CP);
		bin_CP = makeBin(CP);
		BYTE mask = 1 << 7;
		for (i = 0; i < 6 ; i++) 
		{
			if (ind_bit == 8)
			{
				ind_byte++;
				ind_bit = 0;
				bit_mask = 1 << 7;
			}
			setBit(&res[ind_byte], bit_mask, bin_CP, mask);
			ind_bit++;
			bit_mask = bit_mask >> 1;
			mask = mask >> 1;
		}
		curr = curr->next;
	}
}

void setBit(BYTE* dest, BYTE dest_mask, BYTE src, BYTE mask_src)
{
	if (src & mask_src)
	{
		*(dest) = *(dest) | dest_mask;
	}
}

BYTE makeBin(chessPos CP)
{
	BYTE bin_CP = 0, mask;
	int let = CP[0] - 'A';
	int dig = CP[1] - '1';
	int i;

	for (i = 3; i >= 0; i--)
	{
		mask = 1 << i;
		if (mask & let)
		{
			bin_CP = bin_CP | mask;
		}
	}
	bin_CP = bin_CP << 3;
	for (i = 3; i >= 0; i--)
	{
		mask = 1 << i;
		if (mask & dig)
		{
			bin_CP = bin_CP | mask;
		}
	}
	bin_CP = bin_CP << 2;
	return bin_CP;
}

int getbyteSize(int bitSize)
{
	if (bitSize % 8 == 0)
	{
		return bitSize / 8;
	}
	else
	{
		return (bitSize / 8) + 1;
	}
}

void checkFile(FILE* file)
{
	if (file == NULL)
	{
		printf("file opening failed\n");
		exit(1);
	}
}

int checkAndDisplayPathFromFile(char* file_name)
{
	unsigned short fileListSize;
	int ret;
	FILE* file = fopen(file_name, "rb");
	if (file == NULL)
	{
		return -1;
	}
	fread(&fileListSize, sizeof(unsigned short), 1, file);

	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAlloc(lst);
	makeEmptyList(lst);

	makeListFromFile(file, fileListSize, lst);

	ret = checkList(lst);

	fclose(file);
	freeList(lst);
	return ret;
}

int checkList(chessPosList* lst)
{
	unsigned short lstLen;
	int ret;
	if (checkLegit(lst))
	{
		display(lst);
		lstLen = getListSize(lst);
		if (lstLen == SIZE * SIZE)
		{
			ret = 2;
		}
		else
		{
			ret = 3;
		}
	}
	else /*not legitimate knight path*/
	{
		ret = 1;
	}
	return ret;
}

void makeListFromFile(FILE* file, unsigned short listSize, chessPosList* lst)
{
	int i,j , curr_let, curr_dig;
	int byteSize = getbyteSize((int)listSize * 6);

	BYTE* arr = (BYTE*)malloc(byteSize * sizeof(BYTE));
	checkAlloc(arr);
	fread(arr, sizeof(BYTE), byteSize, file);

	makeListFromArr(lst, arr, listSize, byteSize);
	free(arr);
}

void makeListFromArr(chessPosList* lst, BYTE* arr, unsigned short listSize, int byteSize)
{
	int ind_byte = 0, ind_bit = 0, i, j;
	BYTE mask_CP, bit_mask = 1 << 7;
	BYTE CP;
	for (i = 0; i < listSize; i++)
	{
		CP = 0;
		mask_CP = 1 << 7;
		for (j = 0; j < 6; j++) /*get 6 bits that represent row and col*/
		{
			if (ind_bit == 8) /*if end of byte, go to next byte*/
			{
				ind_bit = 0; /*point at most significent bit*/
				ind_byte++;
				bit_mask = 1 << 7; /*new mask for current byte*/
			}
			setBit(&CP, mask_CP, arr[ind_byte], bit_mask);
			ind_bit++; /*next bit in byte*/
			bit_mask = bit_mask >> 1; /*mask for next bit in byte*/
			mask_CP = mask_CP >> 1; 
		}
		insertBinDataToList(CP, lst);
	}
}

void insertBinDataToList(BYTE CP, chessPosList* lst)
{
	int let = extractbit(CP, LET_MASK);
	int dig = extractbit(CP, DIG_MASK);
	insertDatatoEndList(lst, let, dig);
}

int extractbit(BYTE CP, BYTE mask)
{
	int res = 0;
	int mask_res = 1, i;
	for (i = 0; i < 3; i++)
	{
		if (mask & CP)
		{
			res = res | mask_res;
		}
		mask_res = mask_res << 1;
		mask = mask << 1;
	}
	return res;
}

int checkLegit(chessPosList* lst)
{
	int res = 1;
	if (lst != NULL) /*if empty list return legit*/
	{
		chessPosCell* curr = lst->head, * next = lst->head->next;
		while (next != NULL && res)
		{

			if (notNeighbor(curr->position, next->position))
			{
				res = 0;
			}
			curr = next;
			next = curr->next;
		}
	}
	return res;
}

int notNeighbor(chessPos curr, chessPos next)
{
	int cRow, cCol, nRow, nCol, res = 1;
	cRow = curr[LET] - 'A';
	cCol = curr[DIG] - '1';
	nRow = next[LET] - 'A';
	nCol = next[DIG] - '1';

	if (nRow == cRow - 2 && nCol == cCol + 1)
	{
		res--;
		return res;
	}
	if (nRow == cRow - 1 && nCol == cCol + 2)
	{
		res--;
		return res;
	}
	if (nRow == cRow + 1 && nCol == cCol + 2)
	{
		res--;
		return res;
	}
	if (nRow == cRow + 2 && nCol == cCol + 1)
	{
		res--;
		return res;
	}
	if (nRow == cRow + 2 && nCol == cCol - 1)
	{
		res--;
		return res;
	}
	if (nRow == cRow + 1 && nCol == cCol - 2)
	{
		res--;
		return res;
	}
	if (nRow == cRow - 1 && nCol == cCol - 2)
	{
		res--;
		return res;
	}
	if (nRow == cRow - 2 && nCol == cCol - 1)
	{
		res--;
		return res;
	}

	return res;
}