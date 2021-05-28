#include "menu.h"

void menu()
{
	int choice = 0, searchPath = 0;
	chessPos location = { SIZE, SIZE };
	pathTree path_tree;
	//chessPosList lst;
	chessPosList* lst = NULL;

	path_tree.root = NULL;
	while (choice != 6)
	{
		printMenu();
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
			{
				getLocation(location);
				restart(&searchPath, lst, &path_tree);
				break;
			}
			case 2:
			{
				optionTwo(location, &path_tree);
				break;
			}
			case 3:
			{
				lst = optionThree(location, &path_tree, &searchPath);
				break;
			}
			case 4:
			{
				if (!searchPath)
				{
					lst = optionThree(location, &path_tree, &searchPath);
				}
				optionFour(location, lst);

				break;
			}
			case 5:
			{
				optionFive();
				break;
			}
			case 6:
			{
				break;
			}
			default:
			{
				printError(invalid_choice);
				getchar();
				break;
			}
		}
	}
	restart(&searchPath, &lst, &path_tree);
}

void printMenu()
{
	printf("1. Enter a knight's starting position\n" 
			"2. Create all possible knight paths\n"
			"3. Find a knight path covering all board\n"
			"4. Save knight path covering all board to file\n"
			"5. Load and display path from file\n"
			"6. Exit\n"	);
}

void getLocation(chessPos location)
{
	char row, col;
	int valid = 0;
	while (!valid)
	{
		printf("Please enter chess board Position (row, col)\n");
		getchar();
		scanf("%c %c", &row, &col);
		if (isValMove(row, 'A') && isValMove(col, '1'))
		{
			valid = 1;
			location[LET] = row;
			location[DIG] = col;
		}
		else
		{
			printError(invalid_Input);
		}
	}
}

void printError(int error_index)
{
	switch (error_index)
	{
	case invalid_choice:
	{
		printf("Invalid choice, please enter a number between 1-6.\n");
		break;
	}
	case invalid_Input:
	{
		printf("Invalid location.\n");
		break;
	}
	case no_location_given:
	{
		printf("No location given.\n");
		break;
	}
	default:
		break;
	}
}

void optionTwo(chessPos location, pathTree* path_tree)
{
	if (location[LET] == SIZE)
	{
		printError(no_location_given);
	}
	else
	{
		*path_tree = findAllPossibleKnightPaths(location);
	}
}

chessPosList* optionThree(chessPos location, pathTree* path_tree, int* searchPath)
{
	chessPosList* tmpList = NULL;
	if (location[LET] == SIZE)
	{
		printError(no_location_given);
	}
	else
	{
		if (path_tree->root == NULL)
		{
			*path_tree = findAllPossibleKnightPaths(location);
		}
		tmpList = findKnightpathCoveringAllBoard(path_tree);
		if (tmpList->head == NULL)
		{
			printf("There is no full board path from given location.\n");
		}
	}
	*searchPath = 1;
	return tmpList;
}

void optionFour(chessPos location, chessPosList* lst)
{
	if (location[LET] == SIZE)
	{
		printError(no_location_given);
	}
	else
	{
		if (lst->head != NULL)
		{
			char* file_name = getFileName();
			saveListToBinFile(file_name, lst);
			free(file_name);
		}
		else
		{
			printf("There is no full board path from given location.\n");
		}
	}
}

char* getFileName()
{
	printf("Please enter file name and than press ENTER:\n");
	fflush(stdin);
	getchar();
	char* file_name = (char*)malloc(sizeof(char));
	checkAlloc(file_name);
	int logSize = 0, phySize = 1;
	char c = getchar();
	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			file_name = (char*)realloc(file_name, phySize * sizeof(char));
			checkAlloc(file_name);
		}
		file_name[logSize] = c;
		c = getchar();
		logSize++;
	}
	file_name[logSize] = '\0';
	if (logSize < phySize)
	{
		file_name = (char*)realloc(file_name, sizeof(char) * (logSize + 1));
		checkAlloc(file_name);
	}
	return file_name;
}

void optionFive()
{
	int fileRet;
	char* file_name = getFileName();
	fileRet = checkAndDisplayPathFromFile(file_name);
	printCase(fileRet);
	free(file_name);
}

void printCase(int fileRet)
{
	switch (fileRet)
	{
		case -1:
		{
			printf("File does not exist.\n\n");
			break;
		}
		case 1:
		{
			printf("The list contains an illegitimate knight path.\n\n");
			break;
		}
		case 2:
		{
			printf("The knight path in the list covers the entire board.\n\n");
			break;
		}
		case 3:
		{
			printf("The knight path in the list doesn't cover all board's locations.\n\n");
			break;
		}
	}
}

void restart(int* searchPath, chessPosList* lst, pathTree* path_tree)
{
	if (*searchPath)
	{
		freeList(lst);
	}
	freePathTree(*path_tree);
	lst = NULL;
	path_tree->root = NULL;
	*searchPath = 0;
}