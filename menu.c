#include "menu.h"

void menu()
{
	int choice = 0;
	chessPos location = { SIZE, SIZE };
	pathTree path_tree;
	//chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	chessPosList lst;

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
				break;
			}
			case 2:
			{
				optionTwo(location, &path_tree);
				break;
			}
			case 3:
			{
				optionThree(location, &path_tree, &lst);
				break;
			}
			case 4:
			{
				//get file name from user
				//save knoght path covering all board in file
				//if path not found, print error to user
				//if fun 3 didnt chosen, activate it eithout asking
				//if fun 1 didnt happen, print error
			}
			case 5:
			{
			//get file name from user, activate fun 6
			}
			case 6:
			{
				exit(1);
			}
			default:
			{
				printError(invalid_choice);
				break;
			}
		}
	}
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

void optionThree(chessPos location, pathTree* path_tree, chessPosList* lst)
{
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
		lst = findKnightpathCoveringAllBoard(path_tree);
		
		if (lst->head == NULL)
		{
			printf("There is no full board path from given location.\n");
		}
	}

}
