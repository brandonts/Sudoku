/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include <iostream>
#include <vector>
#include <chrono>

#include "Sudoku_Puzzle.h"


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
	auto time1=chrono::steady_clock::now();
	p1=SudokuSolver(p1);
	auto d=chrono::steady_clock::now()-time1;
	p1.Display_();
	cout<<"DONE!\n";
	cout << "solving that puzzle took: "<< chrono::duration_cast<chrono::milliseconds>(d).count() << "ms;";
}

bool OnlyPossible(SudokuPuzzle& x)
{
	bool change=false;
	for(int i; i<9; i++)
	{
		//if(OnlyPossibleBox(x,i))				change=true;
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
								//guess.Display_();
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
