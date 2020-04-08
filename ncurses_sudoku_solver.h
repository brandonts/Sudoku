
#ifndef NCURSES_SUDOKU_SOLVER_H_
#define NCURSES_SUDOKU_SOLVER_H_

#include "sudoku_puzzle.h"
#include "sudoku_logic.h"

void Display(SudokuPuzzle &p1)
{
	move(0,0);
	clear();
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) printw("\n-------------------------\n");
		else printw("\n");
		printw("| ");
		for(int j=0;j<9;j++)
		{
			printw("%i",p1.Read_(i,j));
			if(j==2 || j==5 || j==8) printw(" | ");
			else printw(" ");
		}
	}
	 printw("\n-------------------------\n");
	 refresh();
}

void Display(SudokuPuzzle &p1,int row,int column)
{
	move(0,0);
	clear();
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) printw("\n-------------------------\n");
		else printw("\n");
		for(int j=0;j<9;j++)
		{
			if(j==0) printw("|");
			if(i==row && j==column) printw("(%i)",p1.Read_(i,j));
			else if(i==row && j==column+1) printw("%i",p1.Read_(i,j));
			else printw(" %i",p1.Read_(i,j));
			if(j==2 || j==5 || j==8)
			{
				if(i==row && j==column) printw("| ");
				else printw(" |");
			}
		}
	}
	 printw("\n-------------------------\n");
	 refresh();
}

#endif /* NCURSES_SUDOKU_SOLVER_H_ */
