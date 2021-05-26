#include "compress.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	unsigned short int listSize = getListSize(pos_list);
	int byteSize = getbyteSize(listSize * 6);

	FILE* file = fopen(file_name, "wb");
	checkFile(file);

	fwrite(&listSize, sizeof(unsigned short int), 1, file);

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
	
	BYTE bin_CP;
	BYTE bit_mask = 1 << 7;

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
				setBit(res, bin_CP, mask, ind_byte, bit_mask, &ind_bit);
			}
			else
			{
				setBit(res, bin_CP, mask, ind_byte, bit_mask, &ind_bit);
			}
			bit_mask = bit_mask >> 1;
			mask = mask >> 1;
		}
		curr = curr->next;
	}
}

void setBit(BYTE* res, BYTE bin_CP, BYTE mask, int ind_byte, BYTE bit_mask, int* ind_bit)
{
	if (bin_CP & mask)
	{
		res[ind_byte] = res[ind_byte] | bit_mask;
	}
	(*ind_bit)++;
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
	FILE* file = fopen(file_name, "rb");
	if (file == NULL)
	{
		return -1;
	}
	
	unsigned short int listSize;
	fread(&listSize, sizeof(unsigned short int), 1, file);
	printf("%d\n", listSize);

	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAlloc(lst);
	makeEmptyList(lst);
	makeListFromFile(file, listSize, lst);
	printlist(lst);

	/*
	if(check not legit())
	{
	return 1;
	}
	else
	{
	display(lst);
	if(sizelst == SIZE*SIZE)
	return 2;
	else
	{
	return 3;
	}

	}

	
	*/


}

void makeListFromFile(FILE* file, unsigned short int listSize, chessPosList* lst)
{
	int i,j , curr_let, curr_dig;
	int byteSize = getbyteSize((int)listSize * 6);

	BYTE* arr = (BYTE*)malloc(byteSize * sizeof(BYTE));
	checkAlloc(arr);
	fread(arr, sizeof(BYTE), byteSize, file);

	makeListFromArr(lst, arr, listSize, byteSize);
	printlist(lst);
	
}

void makeListFromArr(chessPosList* lst, BYTE* arr, unsigned short int listSize, int byteSize)
{
	int ind_byte = 0, ind_bit = 0, i, j;
	BYTE mask_CP, bit_mask = 1 << 7;
	BYTE CP;
	for (i = 0; i < listSize; i++)
	{
		CP = 0;
		mask_CP = 1 << 7;
		for (j = 0; j < 6; j++)
		{
			if (ind_bit == 8)
			{
				ind_bit = 0;
				ind_byte++;
				bit_mask = 1 << 7;
				if (bit_mask & arr[ind_byte])
				{
					CP = CP | mask_CP;
				}
			}
			else
			{
				if (bit_mask & arr[ind_byte])
				{
					CP = CP | mask_CP;
				}
			}				
			ind_bit++;
			bit_mask = bit_mask >> 1;
			mask_CP = mask_CP >> 1;
		}
		insertBinDataToList(CP, lst);
	}
}

void insertBinDataToList(BYTE CP, chessPosList* lst)
{
	int let = extractbit(CP, 1 << 5) ;
	int dig = extractbit(CP, 1 << 2) ;
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
