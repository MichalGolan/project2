#ifndef _CHESSPOSTREE_H
	#define _CHESSPOSTREE_H

#include "chessPosArray.h"
#include "chessPosList.h"
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
	struct _treeNodeListCell* next;
};

typedef struct _pathTree
{
	treeNode* root;
} pathTree;

/*C - the function build tree of possible knight paths given for a specific starting position*/
pathTree findAllPossibleKnightPaths(chessPos* startingPosition);

/*build paths tree recursivly*/
treeNode* findPathsRec(chessPos curr, chessPosArray** movesMat, int visited[][SIZE]);

/*create new treeNode */
treeNode* createNewTreeNode(chessPos pos, treeNodeListCell* next_possible_position);

/*insert data to start list*/
void insertDatatoStartListPossiblePos(treeNode* headList, treeNode* currNeighbor);

/* D - find path covering all board, return path if found*/
chessPosList* findKnightpathCoveringAllBoard(pathTree* path_tree);

/*find path covering all board recursivly*/
void findCoveringAllRec(chessPosList* lst, treeNode* root, int counter, int* found);

/*free path tree*/
void freePathTree(pathTree root);

/*free path tree recursivly*/
void freePathTreeRec(treeNode* root);

/*free treeNode List */
void freetreeNodeList(treeNodeListCell* head);


#endif 

