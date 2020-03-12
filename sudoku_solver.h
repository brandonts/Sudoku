/*
 *  sudoku_solver.h
 *
 *  Created on: Sep 27, 2019
 *  Author: Brandon Shaw
 */

#ifndef SUDOKU_SOLVER_H_
#define SUDOKU_SOLVER_H_

#include "sudoku_puzzle.h"

void Display(SudokuPuzzle &p1)
{
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) cout<<"\n-------------------------\n";
		else cout<<"\n";
		cout << "| ";
		for(int j=0;j<9;j++)
		{
			cout << p1.Read_(i,j);
			if(j==2 || j==5 || j==8) cout<<" | ";
			else cout<<" ";
		}
	}
	 cout<<"\n-------------------------\n";
}

void Display(SudokuPuzzle &p1,int row,int column)
{
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) cout<<"\n-------------------------\n";
		else cout<<"\n";
		for(int j=0;j<9;j++)
		{
			if(j==0) cout<<"|";
			if(i==row && j==column) cout<<"("<<p1.Read_(i,j)<<")";
			else if(i==row && j==column+1) cout<<p1.Read_(i,j);
			else cout<<" "<<p1.Read_(i,j);
			if(j==2 || j==5 || j==8)
			{
				if(i==row && j==column) cout<<"| ";
				else cout<<" |";
			}
		}
	}
	 cout<<"\n-------------------------\n";
}

#endif /* SUDOKU_SOLVER_H_ */
