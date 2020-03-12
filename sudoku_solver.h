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
bool OnlyPossible(SudokuPuzzle& x)
{
	bool change=false;
	for(int i=0; i<9; i++)
	{
		//if(OnlyPossibleBox(x,i))				    change=true;
		//if(OnlyPossibleVerticalLine(x,i))		change=true;
		//if(OnlyPossibleHorizontalLine(x,i))	change=true;

	}
	return change;
}
int Solver(SudokuPuzzle& x)
{
	SudokuPuzzle temp=x;
	while(x.Check_()>0) //no exit until puzzle complete or unsolvable
	{
		bool change=false;
		//if(OnlyPossible(x))	change=true;
		//if(Elimination(x))	change=true;

		if(change==false)//This will recursively guess every possible solution until solved
		{
			for(int i=0; i<9; i++)
			{
				for(int j=0; j<9; j++)
				{
					if(temp.Read_(i,j)==0)
					{
						for(int value=1; value<11; value++)
						{
							if(value==10) return -1;//returns -1 when all possible solution has been attempted without valid solution

							if(temp.TestSquare_(i,j,value)) //use 700ns test to prevent 32,000ns Puzzle creation if unnecessary
							{
								SudokuPuzzle guess=temp;
								guess.Write_(i,j,value);
								if(Solver(guess)==0)//when Solver returns check if puzzle is solved
								{
									if(guess.Check_()==0)x=guess;//when puzzle is complete asigns guess to &x
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	if(temp.Check_()==-1) return -1;
	return 0;
}

SudokuPuzzle SudokuSolver(SudokuPuzzle x)
{
	Solver(x);
	return x;
}
#endif /* SUDOKU_SOLVER_H_ */
