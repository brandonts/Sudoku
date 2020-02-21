/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include <iostream>
#include <vector>
#include <chrono>

#include "sudoku_solver.h"
#include "sudoku_puzzle.h"


using namespace std;

void TestEmptyPuzzle()
{
	cout<<"Begin empty puzzle test\n";
	SudokuPuzzle p1{};
	p1.Display_();
	p1=SudokuSolver(p1);
	p1.Display_();
	cout<<"Empty puzzle test complete.\n";
}

void TestSpecificPuzzle()
{
	cout<<"Begin specific puzzle test.\n";
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
	auto time1=chrono::steady_clock::now();
	p1=SudokuSolver(p1);
	auto d=chrono::steady_clock::now()-time1;
	p1.Display_();
	cout<<"Specific Puzzle test complete.\n";
}

int main()
{
	TestEmptyPuzzle();
	TestSpecificPuzzle();
	return 0;
}
