
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H

#include "ChessPosList.h"
#include "ChessPosArray.h"
#include "ChessPossTree.h"

chessPosArray*** validKnightMoves();
/*A - the function returns a two-dimensional array,
where in every cell there is an array of chess positions to where a knight
can move from this cell*/

void display(chessPosList* lst);
/*B - the function receives a list of moves and displays them on the screen in a chess board
the function also removes multiple occurences of a move and leaves only the first occurence*/

pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
/*C - the function build tree of possible knight paths given for a specific starting position*/


#endif