/*
 * sudoku_solver.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include "sudoku_logic_stack.h"
#include "sudoku_puzzle.h"

#include <iostream>

namespace basic
{
void Display(SudokuPuzzle &p1,int row,int column);
void Display(SudokuPuzzle &p1);

int basic_interface()
{
	std::cout<<"\nWelcome to Sudoku_Solver!\n";

	SudokuPuzzle p1{};
	char input{};
	int value=-1;
	int row=0;
	int col=0;

	while(true)
	{
		std::cin.clear();
		value=-1;

		Display(p1,row,col);
		std::cout<<"(wasd) to select (e)input (x)solve (q)quit: ";
		std::cin>>input;
		if(input=='e')
		{
			while(value<0 || value>9)
			{
				std::cin.clear();
				std::cout<<"Enter value 0-9: ";
				std::cin>>value;
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
			std::cout<<"\nNow Solving Your Puzzle.\n";
			SudokuPuzzle p2=SudokuSolver(p1);
			if(p1==p2)std::cout<<"\nYour Puzzle can not be solved as is.\n";
			else
			{
				Display(p2);
				std::cout<<"Here is your Solved Puzzle!\n\n";
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
		if(i==0 || i==3 || i==6) std::cout<<"\n-------------------------\n";
		else std::cout<<"\n";
		std::cout << "| ";
		for(int j=0;j<9;j++)
		{
			std::cout << p1.Read_(i,j);
		        if(j==2 || j==5 || j==8) std::cout<<" | ";
		        else std::cout<<" ";
		}
	}
	std::cout<<"\n-------------------------\n";
}
 
void Display(SudokuPuzzle &p1,int row,int column)
{
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) std::cout<<"\n-------------------------\n";
		else std::cout<<"\n";
		for(int j=0;j<9;j++)
		{
			if(j==0) std::cout<<"|";
			if(i==row && j==column) std::cout<<"("<<p1.Read_(i,j)<<")";
			else if(i==row && j==column+1) std::cout<<p1.Read_(i,j);
			else std::cout<<" "<<p1.Read_(i,j);
			if(j==2 || j==5 || j==8)
			{
				if(i==row && j==column) std::cout<<"| ";
				else std::cout<<" |";
			}
                 }
         }
	std::cout<<"\n-------------------------\n";
}
}
