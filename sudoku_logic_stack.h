#ifndef SUDOKU_LOGIC_H_
#define SUDOKU_LOGIC_H_

#include "Sudoku_Puzzle/sudoku_puzzle.h"

//calls Solver() because Solver() is recurisve and so couldn't return required SudokuPuzzle itself
//also has some debug code
SudokuPuzzle SudokuSolver(SudokuPuzzle x);

int Solver(SudokuPuzzle& x);//Primary Loop includes recursive guess when logic fails

//returns 0 and writes value when finds onlypossible, returns -1 when none are found
//only finds one per call
int OnlyPossible(SudokuPuzzle &x);

//for each square checks box,row, and col to eliminate values-writes if one is left
//only finds one per call
int Elimination(SudokuPuzzle &x);

//checks each box to see if it only has empty squares on one of its rows or columns
//if it does it tests the squares on that row or col that are not in the box with
//elimination test that also eliminates the values that go in the empty spots in then
//row or column of the box
int BlockLineElimination(SudokuPuzzle &x);

//checks each box to see if any of its rows or cols have the only squares in that box
//that can hold any value. when it finds such a row or col it it runs an elimination
//type sweep of the row or col with those values blocked
int BlockLineValueElimination(SudokuPuzzle &x);

#endif /* SUDOKU_LOGIC_H_ */
