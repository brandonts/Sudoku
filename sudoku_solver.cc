/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include "sudoku_logic_stack.h"
#include "sudoku_puzzle.h"

#include <iostream>

using namespace std;

void Display(SudokuPuzzle &p1,int row,int column);
void Display(SudokuPuzzle &p1);

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
		cout<<"(wasd) to select (e)input (x)solve (q)quit: ";
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

