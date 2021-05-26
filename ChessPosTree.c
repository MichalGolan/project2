#include "ChessPossTree.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	int visitedTable[SIZE][SIZE] = { 0 };
	chessPosArray*** movesMat = validKnightMoves();
	pathTree treePath;
	treePath.root = findPathsRec(*startingPosition, *movesMat, visitedTable);

	return treePath;
}

chessPosList* findKnightpathCoveringAllBoard(pathTree* path_tree)
{
	int counter = 1;
	int found = FALSE;
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAlloc(lst);
	makeEmptyList(lst);
	findCoveringAllRec(lst, path_tree->root, counter, &found );
	return lst;
}

void findCoveringAllRec(chessPosList* lst, treeNode* root, int counter, int* found)
{
	if (root->next_possible_position == NULL)
	{
		if (counter == SIZE * SIZE)
		{
			*found = TRUE;
			insertDataToList(lst, root->position);
		}
		return;
	}
	else
	{
		treeNodeListCell* curr = root->next_possible_position;
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

treeNode* findPathsRec(chessPos curr, chessPosArray** movesMat, int visited[][SIZE])
{
	int row = curr[LET] - 'A';
	int col = curr[DIG] - '1';
	int i;

	if (visited[row][col])
	{
		return NULL;
	}
	else
	{
		treeNode* currNeighbor;
		visited[row][col] = 1;
		treeNode* newNode = createNewTreeNode(curr, NULL);
		chessPosArray neighbors = movesMat[row][col];

		for (i = 0; i < (neighbors.size); i++)
		{

			chessPos* tmp = neighbors.positions;
			currNeighbor = findPathsRec(*(tmp + i), movesMat, visited);
				if (currNeighbor != NULL)
				{
					insertDatatoStartListPossiblePos(newNode, currNeighbor);
				}
		}
		visited[row][col] = 0;
		return newNode;
	}
}


void insertDatatoStartListPossiblePos(treeNode* headList, treeNode* currNeighbor)
{
	treeNodeListCell* newListCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	newListCell->node = currNeighbor;
	newListCell->next = headList->next_possible_position;
	headList->next_possible_position = newListCell;
}

treeNode* createNewTreeNode(chessPos pos, treeNodeListCell* next_possible_position)
{
	treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
	checkAlloc(newNode);
	copyChessPos(pos, newNode->position);
	newNode->next_possible_position = next_possible_position;
	return newNode;
}

void freePathTree(pathTree root)
{
	freePathTreeRec(root.root);
}

void freePathTreeRec(treeNode* root)
{
	if (root->next_possible_position == NULL)
	{
		free(root);
		return;
	}
	else
	{
		freetreeNodeList(root->next_possible_position);
		free(root);
	}
}

void freetreeNodeList(treeNodeListCell* head)
{
	treeNodeListCell* curr = head, *next;
	while (curr != NULL)
	{
		freePathTreeRec(curr->node);
		next = curr->next;
		free(curr);
		curr = next;
	}

}
