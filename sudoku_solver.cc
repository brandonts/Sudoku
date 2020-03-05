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
	cout<<"\nWelcome to Sudoku_Solver!\n";

	SudokuPuzzle p1{};
	char input{};
	int value=-1;
	int row=0;
	int col=0;

	while(true)
	{
		cin.clear();
		value=-1;

		Display(p1,row,col);
		cout<<"(wasd) to move X (e)input (x)solve (q)quit: ";
		cin>>input;
		if(input=='e')
		{
			while(value<0 || value>9)
			{
				cin.clear();
				cout<<"Enter value 0-9: ";
				cin>>value;
			}
			p1.Write_(row,col,value);
			if(col<8)col++;else {col=0;row++;}
		}else if(input=='w'){if(row==0)row+=8;else row-=1;}
		else if(input=='a'){if(col==0)col+=8;else col-=1;}
		else if(input=='s'){if(row==8)row-=8;else row+=1;}
		else if(input=='d')
			{
				if(col==8)
				{
					if(row!=8){col-=8;row+=1;}else{col=0;row=0;}
				}else col+=1;
			}
		else if(input=='q')break;
		else if(input=='x')
		{
			cout<<"\nNow Solving Your Puzzle.\n";
			SudokuPuzzle p2=SudokuSolver(p1);
			if(p1==p2)cout<<"\nYour Puzzle can not be solved as is.\n";
			else
			{
				Display(p2);
				cout<<"Here is your Solved Puzzle!\n\n";
				break;
			}
		}else Display(p1,row,col);
	}

	return 0;
}
