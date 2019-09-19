/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */
#include "Sudoku_Puzzle.h"

#include <iostream>
#include <vector>


using namespace std;

SudokuPuzzle SudokuSolver(SudokuPuzzle x);

int main()
{
	vector<int> test
	{
		0,3,5,7,0,9,4,0,0,
		7,0,1,4,0,0,0,0,0,
		0,9,0,0,2,0,0,5,0,
		0,6,3,0,4,0,2,7,0,
		1,0,0,0,0,0,0,0,9,
		0,7,8,0,9,0,6,1,0,
		0,5,0,0,6,0,0,8,0,
		0,0,0,0,0,8,7,0,5,
		0,0,6,5,0,1,9,4,0
	};

	SudokuPuzzle p1{test};

	p1.Display_();
	for(int i=0; i<9; i++)
		for(int j=0; j<9; j++)
			p1.Write_(i,j,5);
	p1.Display_();

	SudokuSolver(p1);

}

SudokuPuzzle SudokuSolver(SudokuPuzzle x)
{
	return x;
}




