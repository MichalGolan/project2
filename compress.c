#include "compress.h"

void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	short int listSize = getListSize(pos_list);
	int byteSize = getbyteSize(listSize * 6);

	FILE* file = fopen(file_name, "wb");
	checkFile(file);

	fwrite(&listSize, sizeof(short int), 1, file);

	BYTE* res = (BYTE*)calloc(byteSize, sizeof(BYTE));
	checkAlloc(res);

	fillArrFromList(pos_list, res, byteSize, listSize);

	fwrite(res, sizeof(BYTE), byteSize, file);

	fclose(file);
	free(res);
}

void fillArrFromList(chessPosList* pos_list, BYTE* res, int arrSize, short int listSize)
{
	chessPosCell* curr = pos_list->head;
	chessPos CP;
	int ind_byte = 0, ind_bit=0, i;
	
	BYTE bin_CP;
	BYTE mask_byte = 1 << 7;

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
				mask_byte = 1 << 7;
				setBit(res, bin_CP, mask, ind_byte, mask_byte, &ind_bit);
				/*
				if (bin_CP & mask)
				{
					res[ind_byte] = res[ind_byte] | mask_byte;
				}
				ind_bit++;
				mask_byte >> 1;*/
			}
			else
			{
				setBit(res, bin_CP, mask, ind_byte, mask_byte, &ind_bit);
				/*if (bin_CP & mask)
				{
					res[ind_byte] = res[ind_byte] | mask_byte;
				}
				ind_bit++;
				mask_byte >> 1;*/
			}
			mask_byte = mask_byte >> 1;
			mask = mask >> 1;
		}
		curr = curr->next;
	}
}

void setBit(BYTE* res, BYTE bin_CP, BYTE mask, int ind_byte, BYTE mask_byte, int* ind_bit)
{
	if (bin_CP & mask)
	{
		res[ind_byte] = res[ind_byte] | mask_byte;
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


