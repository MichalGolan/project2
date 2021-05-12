#include "ChessPossTree.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	stringArray stringTable[SIZE][SIZE];
	initializeStringTable(stringTable);

	pathTree treePath;
	treePath.root = findPathsRec(*startingPosition, *validKnightMoves(), stringTable, "1", '0');

	printSquare(stringTable[2][2]); /**/

	return treePath;
}

chessPosList* findKnightpathCoveringAllBoard(pathTree* path_tree)
{
	int counter = 0;
	int found = FALSE;
	chessPosList lst;
	makeEmptyList(&lst);

	findCoveringAllRec(&lst, path_tree->root, counter, &found );

	return &lst;
}

void findCoveringAllRec(chessPosList* lst, treeNode* root, int counter, int* found)
{
	if (root->next_possible_position == NULL)
	{
		/*if (counter == SIZE * SIZE)*/
		if (counter == 5)
		{
			*found = TRUE;
			insertDataToList(lst, root->position);
		}
		return;
	}
	else
	{
		treeNodeListCell* curr = root->next_possible_position;
		chessPosCell* newCell;
		while (curr != NULL && *found == FALSE)
		{
			findCoveringAllRec(lst, curr->node, counter+1, found);
			if (*found == TRUE)
			{
				insertDataToList(lst, root->position);
			}
			else
			{
				curr = curr->next;
			}
		}
		return;
	}
}


void printSquare(stringArray square)
{
	int size = square.logSize;
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d: %s\n",i, *(square.stringArray + i));
	}
}
treeNode* findPathsRec(chessPos curr, chessPosArray** movesMat, stringArray stringTable[][SIZE], char* pathId, char newIndex)
{
	int row = curr[LET] - 'A';
	int col = curr[DIG] - '1';
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
		chessPosArray neighbors = movesMat[row][col];

		for (i = 0; i < (neighbors.size); i++)
		{
			chessPos* tmp = neighbors.positions;
			currNeighbor = findPathsRec(*(tmp + i), movesMat, stringTable, newId, i + '1');
				if (currNeighbor != NULL)
				{
					insertDatatoStartListPossiblePos(newNode, currNeighbor);
				}
		}
		/*free newId*/
		return newNode;
	}
}

/*this function fill a string array with codes of paths passed in specific location*/
void insertToStringTable(char* Id, stringArray* strArr)
{
	if (strArr->phySize == 0)
	{
		strArr->phySize = 1;
		strArr->stringArray = (char**)malloc(sizeof(char*));
	}
	else if (strArr->logSize >= strArr->phySize)
	{
		strArr->stringArray = (char**)realloc(strArr->stringArray, 2 * strArr->phySize * sizeof(char*));
		strArr->phySize = 2 * strArr->phySize;
	}

	int size = strlen(Id);
	*(strArr->stringArray + strArr->logSize) = (char*)malloc((size + 1) * sizeof(char));
	strcpy(*(strArr->stringArray + strArr->logSize), Id);
	strArr->logSize++;
}
/*typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_position;
} treeNode;

struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListNodeCell* next;
};*/
void insertDatatoStartListPossiblePos(treeNode* headList, treeNode* currNeighbor)
{
	treeNodeListCell* newListCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	newListCell->node = currNeighbor;
	newListCell->next = headList->next_possible_position;
	headList->next_possible_position = newListCell;
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
		i++;
	}
	return res;
}

/*this function create injective string for specific path*/
char* createID(char* pathIndex, char newIndex)
{
	if (newIndex != '0')
	{
		int i;
		int size = strlen(pathIndex);
		char* newPathIndex = (char*)malloc((size + 2) * sizeof(char));
		for (i = 0; i < size; i++)
		{
			newPathIndex[i] = pathIndex[i];
		}
		newPathIndex[i] = newIndex;
		newPathIndex[i + 1] = '\0';
		return newPathIndex;
	}
	else
	{
		return pathIndex;
	}
}