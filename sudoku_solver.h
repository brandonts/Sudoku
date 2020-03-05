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

		if(change==false)//This will grind out the answer when more elegant solutions fail
		{
			for(int i=0; i<9; i++)
			{
				for(int j=0; j<9; j++)
				{
					if(temp.Read_(i,j)==0)
					{
						for(int value=1; value<11; value++)
						{
							if(value==10) return -1;
							SudokuPuzzle guess=temp;
							//if(guess.TestSquare_(i,j,value)) //this test actually makes program slower(48ms vs3 8ms)
							{
								guess.Write_(i,j,value);
								//Display(guess);
								Solver(guess);
							}
							if(guess.Check_()==0)
							{
								x=guess;
								return 0;
							}
						}
					}
				}
			}
		}
	}
	if(temp.Check_()==-1) return -1;
	x=temp;
	return 0;
}

SudokuPuzzle SudokuSolver(SudokuPuzzle x)
{
	Solver(x);
	return x;
}
#endif /* SUDOKU_SOLVER_H_ */
