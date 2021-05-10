#ifndef _CHESSPOSTREE_H
	#define _CHESSPOSTREE_H

#include "chessPosArray.h"
//#include "chessPosList.h"
//#include "ProjectMainFunctions.h"


typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_position;
} treeNode;

struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListNodeCell* next;
};

typedef struct _pathTree
{
	treeNode* root;
} pathTree;

typedef struct _stringArray
{
	int logSize;
	int phySize;
	char** stringArray;
} stringArray;

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
/*C - the function build tree of possible knight paths given for a specific starting position*/


void printSquare(stringArray square);

treeNode* createNewTreeNode(chessPos pos, treeNodeListCell* next_possible_position);
treeNode* findPathsRec(chessPos curr, chessPosArray** movesMat, stringArray stringTable[][SIZE], char* pathId, char newIndex);
void insertDatatoStartListPossiblePos(treeNode* headList, chessPos newPos);
int isVisited(char* pathIndex, stringArray square);
void initializeStringTable(stringArray stringTable[][SIZE]);
int strcomp(char* pathIndex, char* str);
char* createID(char* pathIndex, char newIndex);
void insertToStringTable(char* Id, stringArray* strArr);



#endif 

