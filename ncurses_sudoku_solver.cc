#include <ncurses.h>
#include "ncurses_sudoku_solver.h"

int main()
{
  initscr();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);

  SudokuPuzzle p1{};
  char input{};
  int value=-1;
  int row=0;
  int col=0;

  while(true)
  {
    value=-1;

    Display(p1,row,col);
    printw("(wasd) to select, (x)solve (c)clear (q)quit: ");
    input=getch();
    value=input-'0';

    if(input=='0'||input=='1'||input=='2'||input=='3'||input=='4'||input=='5'||input=='6'||input=='7'||input=='8'||input=='9')
    {
      p1.Write_(row,col,value);
      if(col<8)col++;else {col=0;row++;}
    }
    else if(input=='w'){if(row==0)row+=8;else row-=1;}
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
    else if(input=='c')
    {
      printw("Are you sure (y/n)?");
      while(true)
      {
        char ch=getch();
        if(ch=='y'){p1={};break;}
        if(ch=='n')break;
      }
    }
    else if(input=='x')
    {
      printw("\nNow Solving Your Puzzle.\n");
      SudokuPuzzle p2=SudokuSolver(p1);
      if(p1==p2)printw("\nYour Puzzle can not be solved as is.\n");
      else
      {
        Display(p2);
        printw("Here is your Solved Puzzle!");
        getch();
      }
    }else Display(p1,row,col);
  }

  endwin();
  return 0;
}
