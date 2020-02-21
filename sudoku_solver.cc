/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include "sudoku_solver.h"
#include "sudoku_puzzle.h"

#include <iostream>
using namespace std;

int main()
{
	cout<<"\nWelcome to Sudoku_Solver!\n\n";
	cout<<"Begin entering puzzle numbers from top left to right.(zero for empty)\n";
	SudokuPuzzle p1{};
	int input=0;
	p1.Display_();
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cout<<"next: ";
			cin>>input;// needs validation
			p1.Write_(i,j,input);
			p1.Display_();
		}
	}
	cout<<"Now Solving Your Puzzle.\n\n";
	p1=SudokuSolver(p1);
	p1.Display_();
	return 0;
}
