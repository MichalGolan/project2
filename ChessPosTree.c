#include "ChessPossTree.h"

treeNode* findPathsRec(chessPos curr, chessPosArray*** movesMat, stringArray** stringTable, char* pathId, char newIndex)
{
	int row = curr[LET];
	int col = curr[DIG];
	int i;
	treeNode* currNeighbor;
	if (isVisited(pathId, stringTable[row][col]))
	{
		return NULL;
	}
	else
	{
		char* newId = createID(pathId, newIndex);
		insertToStringTable(newId, &(stringTable[row][col]));

		treeNode* newNode = createNewTreeNode(curr, NULL);
		chessPosArray* neighbors = *(*(movesMat)+row)+col;

		for (i = 0; i < (neighbors->size); i++)
		{
			currNeighbor = findPathsRec(*(neighbors->positions + i), movesMat, stringTable, pathId, i + '0');
				if (currNeighbor != NULL)
				{
					insertDatatoStartListPossiblePos(newNode, *(neighbors->positions + i));
				}
		}
		return newNode;
	}
}

/*this function fill a string array with codes of paths passed in specific location*/
void insertToStringTable(char* Id, stringArray* strArr)
{
	if (strArr->phySize == 0)
	{
		strArr->phySize = 1;
		char** newStrArr = (char**)malloc(sizeof(char*));
	}
	else if (strArr->logSize >= strArr->phySize)
	{
		char** newStrArr = (char**)realloc(strArr, 2 * strArr->phySize * sizeof(char*));
		strArr->phySize = 2 * strArr->phySize;
	}
	*(strArr->stringArray + strArr->logSize) = Id;
	
	strArr->logSize++;
}

void insertDatatoStartListPossiblePos(treeNode* headList, chessPos newPos)
{
	treeNode* newNode = createNewTreeNode(newPos, headList->next_possible_position);
	headList->next_possible_position = newNode;
}

void initializeStringTable(stringArray stringTable[][SIZE])
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			stringTable[i][j].logSize = 0;
			stringTable[i][j].phySize = 0;
			stringTable[i][j].stringArray = NULL;
		}
	}
}
 
treeNode* createNewTreeNode(chessPos pos, treeNodeListCell* next_possible_position)
{
	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkAlloc(newNode);
	copyChessPos(pos, newNode->position);
	newNode->next_possible_position = next_possible_position;
	return newNode;
}


int isVisited(char* pathIndex, stringArray square)
{
	int i;
	int res = FALSE;
	if (square.logSize == 0)
	{
		return res;
	}
	else
	{
		for (i = 0; i < square.logSize && res == FALSE; i++)
		{
			if (strcomp(pathIndex, *(square.stringArray + i)))
			{
				res = TRUE;
			}
			
		}
	}
	return res;
}

/*this function compare two strings, if one pathIndex includes the str, return true*/
int strcomp(char* pathIndex, char* str)
{
	int i = 0;
	int res = TRUE;
	while (str[i] != '\0' && res == TRUE)
	{
		if (pathIndex[i] != str[i])
		{
			res = FALSE;
		}
	}
	return res;
}

char* createID(char* pathIndex, char newIndex)
{
	int i;
	int size = strlen(pathIndex);
	char* newPathIndex = (char*)malloc((size + 2) * sizeof(size));
	for (i = 0; i < size; i++)
	{
		newPathIndex[i] = pathIndex[i];
	}
	newPathIndex[i] = newIndex;
	newPathIndex[i + 1] = '\0';

	return newPathIndex;
}