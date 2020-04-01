/*
 * sudoku_puzzle.h
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#ifndef SUDOKU_PUZZLE_H_
#define SUDOKU_PUZZLE_H_

#include <iostream>
#include <vector>

using namespace std;

#define DEBUG false

#if DEBUG
int guess_counter=0;
int only_counter=0;
int elimination_counter=0;
int blockElimination_counter=0;
int valueElimination_counter=0;
#endif

class SudokuPuzzle
{
	private:
		vector<int> table;

	public:
		void Display_();
		SudokuPuzzle();
		SudokuPuzzle(vector<int> v);
		bool operator==(const SudokuPuzzle &other);
		bool operator==(const vector<int> &other);
		bool operator!=(const vector<int> &other);
		void Write_(int row, int column, int value);//writes value to a square
		int Read_(int row, int column);//reads value from a square
		int Check_();//returns -1 if puzzle has become inconsistent, returns the number of empty square otherwise
		int SearchBox_(int box_number,int search_value);//returns how many times a search_value is found in a box
		int SearchVerticalLine_(int line_number,int search_value);//returns how many times a search_value is found in a column
		int SearchHorizontalLine_(int line_number,int search_value);//returns how many times a search_value is found in a row
		bool TestSquare_(int row, int column, int search_value);//returns true when square could hold search_value withought makeing the puzzle inconsistent
		int FindBox_(int row,int column);//returns index of box that a square(0-80))is in

};

SudokuPuzzle::SudokuPuzzle()
{
	for(int i=0; i<81; i++) table.push_back(0);
	if(table.size()!=81) throw invalid_argument("SudokuPuzzle::SudokuPuzzle: vector not size 81");
}

SudokuPuzzle::SudokuPuzzle(vector<int> v)
{
	if(v.size()!=81) throw invalid_argument("SudokuPuzzle::SudokuPuzzle: vector not size 81");
	table=v;
}

bool SudokuPuzzle::operator==(const SudokuPuzzle &other)
{
	return(this->table==other.table);
}

bool SudokuPuzzle::operator==(const vector<int> &other)
{
	return(this->table==other);
}

bool SudokuPuzzle::operator!=(const vector<int> &other)
{
	return !(this->operator==(other));
}

void SudokuPuzzle::Display_()
{
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) cout<<"\n-------------------------\n";
		else cout<<"\n";
		cout << "| ";
		for(int j=0;j<9;j++)
		{
			cout << this->Read_(i,j);
			if(j==2 || j==5 || j==8) cout<<" | ";
			else cout<<" ";
		}
	}
	 cout<<"\n-------------------------\n";
}

void SudokuPuzzle::Write_(int row, int column, int value)
{
	if(row<0 || row>8) throw invalid_argument("SudokuPuzzle::Write_: 0-8 allowed for row");
	if(column<0 || column>8) throw invalid_argument("SudokuPuzzle::Write_: 0-8 allowed for column");
	int square=(row*9+column);
	if(square>80) throw invalid_argument("SudokuPuzzle::Write_: out of bounds 0-80 required");
	table[square]=value;
}

int SudokuPuzzle::Read_(int row, int column)
{
	if(row<0 || row>8) throw invalid_argument("SudokuPuzzle::Read_: 0-8 allowed for row");
	if(column<0 || column>8) throw invalid_argument("SudokuPuzzle::Read_: 0-8 allowed for column");
	return table[row*9+column];
}

//returns -1 if puzzle has become inconsistent, returns the number of empty square otherwise
int SudokuPuzzle::Check_()
{
	for(int i=0; i<9; i++)//returns -1 if any values are found twice in any box,row, or column
	{
		for(int j=1; j<9; j++)
		{
			if(SearchBox_(i,j)>1) 			return(-1);
			if(SearchVerticalLine_(i,j)>1) 	return(-1);
			if(SearchHorizontalLine_(i,j)>1)return(-1);
			if(Read_(i,j)>9 || Read_(i,j)<0)return(-1);
		}
	}
	int empty_squares=0;
	for(int i=0; i<81; i++) if(table[i]==0) empty_squares++;
	return empty_squares;
}

int SudokuPuzzle::SearchBox_(int box_number,int search_value)
{//returns how many times a search_value is found in a box
	int count=0;
	int b=0;
	switch(box_number)
	{
		case 0: b=0;	break;
		case 1: b=3;	break;
		case 2: b=6;	break;
		case 3: b=27;	break;
		case 4: b=30;	break;
		case 5: b=33;	break;
		case 6: b=54;	break;
		case 7: b=57;	break;
		case 8: b=60;	break;
		default: throw invalid_argument("SudokuPuzzle::SearchBox_: out of bounds 0-8 required");
	}

	if(table[b]==search_value)		count++;
	if(table[b+1]==search_value)	count++;
	if(table[b+2]==search_value)	count++;
	if(table[b+9]==search_value)	count++;
	if(table[b+10]==search_value) 	count++;
	if(table[b+11]==search_value) 	count++;
	if(table[b+18]==search_value) 	count++;
	if(table[b+19]==search_value) 	count++;
	if(table[b+20]==search_value) 	count++;

	return count;
}

int SudokuPuzzle::SearchVerticalLine_(int line_number,int search_value)
{
	if(line_number<0 || line_number>8) throw invalid_argument("SudokuPuzzle::SearchVerticalLine: out of bounds 0-8 required");
	int count=0;
	for(int i=line_number; i<81; i+=9)	if(table[i]==search_value) count++;

	return count;
}

int SudokuPuzzle::SearchHorizontalLine_(int line_number,int search_value)
{
	int count=0;
	int b=0;
	switch(line_number)
	{
		case 0: b=0;	break;
		case 1: b=9;	break;
		case 2: b=18;	break;
		case 3: b=27;	break;
		case 4: b=36;	break;
		case 5: b=45;	break;
		case 6: b=54;	break;
		case 7: b=63;	break;
		case 8: b=72;	break;
		default: throw invalid_argument("SudokuPuzzle::SearchHorizontalLine_: out of bounds 0-8 required");
	}
	for(int i=0; i<9 ; i++) if(table[b+i]==search_value) count++;

	return count;
}

int SudokuPuzzle::FindBox_(int row, int column)
{
	if(0>row || row>8 || 0>column || column>8) throw invalid_argument("SudokuPuzzle::TestSquare_: out of bounds 0-8 required");
	int square=row*9+column;
	if(square<0 || square>80) throw invalid_argument("SudokuPuzzle::FindBox_: out of bounds 0-80 required");
	switch(square)
	{
		case 0:	return 0; break;
		case 1:	return 0; break;
		case 2:	return 0; break;
		case 3:	return 1; break;
		case 4:	return 1; break;
		case 5:	return 1; break;
		case 6:	return 2; break;
		case 7:	return 2; break;
		case 8:	return 2; break;
		case 9:	return 0; break;
		case 10:return 0; break;
		case 11:return 0; break;
		case 12:return 1; break;
		case 13:return 1; break;
		case 14:return 1; break;
		case 15:return 2; break;
		case 16:return 2; break;
		case 17:return 2; break;
		case 18:return 0; break;
		case 19:return 0; break;
		case 20:return 0; break;
		case 21:return 1; break;
		case 22:return 1; break;
		case 23:return 1; break;
		case 24:return 2; break;
		case 25:return 2; break;
		case 26:return 2; break;
		case 27:return 3; break;
		case 28:return 3; break;
		case 29:return 3; break;
		case 30:return 4; break;
		case 31:return 4; break;
		case 32:return 4; break;
		case 33:return 5; break;
		case 34:return 5; break;
		case 35:return 5; break;
		case 36:return 3; break;
		case 37:return 3; break;
		case 38:return 3; break;
		case 39:return 4; break;
		case 40:return 4; break;
		case 41:return 4; break;
		case 42:return 5; break;
		case 43:return 5; break;
		case 44:return 5; break;
		case 45:return 3; break;
		case 46:return 3; break;
		case 47:return 3; break;
		case 48:return 4; break;
		case 49:return 4; break;
		case 50:return 4; break;
		case 51:return 5; break;
		case 52:return 5; break;
		case 53:return 5; break;
		case 54:return 6; break;
		case 55:return 6; break;
		case 56:return 6; break;
		case 57:return 7; break;
		case 58:return 7; break;
		case 59:return 7; break;
		case 60:return 8; break;
		case 61:return 8; break;
		case 62:return 8; break;
		case 63:return 6; break;
		case 64:return 6; break;
		case 65:return 6; break;
		case 66:return 7; break;
		case 67:return 7; break;
		case 68:return 7; break;
		case 69:return 8; break;
		case 70:return 8; break;
		case 71:return 8; break;
		case 72:return 6; break;
		case 73:return 6; break;
		case 74:return 6; break;
		case 75:return 7; break;
		case 76:return 7; break;
		case 77:return 7; break;
		case 78:return 8; break;
		case 79:return 8; break;
		case 80:return 8; break;
		default:throw invalid_argument("SudokuPuzzle::FindBox_: out of bounds 0-80 required");
	}
	return -1;
}

//returns true when square could hold search_value withought makeing the puzzle inconsistent
bool SudokuPuzzle::TestSquare_(int row, int column, int value)
{
	return (!(this->SearchBox_(this->FindBox_(row,column),value) ||
						this->SearchVerticalLine_(column,value) ||
						this->SearchHorizontalLine_(row,value)));
}

int BlockLineOnlyPossible(SudokuPuzzle &x, int box)
{
	int row_start=0;
	int row_end=0;
	int col_start=0;
	int col_end=0;

	switch(box)
	{
		case 0: row_start=0; row_end=2; col_start=0; col_end=2; break;
		case 1: row_start=0; row_end=2; col_start=3; col_end=5; break;
		case 2: row_start=0; row_end=2; col_start=6; col_end=8; break;
		case 3: row_start=3; row_end=5; col_start=0; col_end=2; break;
		case 4: row_start=3; row_end=5; col_start=3; col_end=5; break;
		case 5: row_start=3; row_end=5; col_start=6; col_end=8; break;
		case 6: row_start=6; row_end=8; col_start=0; col_end=2; break;
		case 7: row_start=6; row_end=8; col_start=3; col_end=5; break;
		case 8: row_start=6; row_end=8; col_start=6; col_end=8; break;
		default: return -1;
	}
	//scan rows of box for blocked row
	for(int i=row_start; i<=row_end;i++)
	{
		int count=0;
		for(int j=col_start; j<=col_end; j++)
		{
			if(x.Read_(i,j)==0) count++;
		}
		if(count!=0 && count==x.SearchBox_(box,0))
		{
			//BLOCKROW
			for(int col=0; col<9; col++)
			{
				if(col<col_start || col>col_end) x.Write_(i,col,-1);
			}
			return 0;
		}else if(count>1)return -1;//if a row has more than one possible then no need to check columns
	}
	//scan cols of box for blocked cols
	for(int j=col_start; j<=col_end; j++)
	{
		int count=0;
		for(int i=row_start; i<=row_end;i++)
		{
			if(x.Read_(i,j)==0) count++;
		}
		if(count!=0 && count==x.SearchBox_(box,0))
		{
			//BLOCKCOL
			for(int row=0; row<9; row++)
			{
				if(row<row_start || row>row_end) x.Write_(row, j, -1);
			}
			return 0;
		}
	}
	return -1;
}

//returns 0 and writes value when finds onlypossible, returns -1 when none are found
//only finds one per call
int OnlyPossible(SudokuPuzzle &x)
{
	for(int value=1; value<10; value++)
	{
		SudokuPuzzle temp=x;
		//writes -1 to all squares that have non value value or cant be value
		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				int y=temp.Read_(i,j);
				if(y!=value)
				{
					if(y!=0)
					{
						temp.Write_(i,j,-1);
					}else if(y==0){if(temp.TestSquare_(i,j,value)==false)temp.Write_(i,j,-1);}
				}
			}
		}
		//scans each box for places where value is restricted to a row or col then
		//writes -1 to all squares in that row or col of the Puzzle that are not in the box.
		for(int box=0; box<9; box++)
		{
			BlockLineOnlyPossible(temp, box);
		}
		//check each Box to see if it has Only one possible spot for value
		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				if(temp.Read_(i,j)==0)
				{
					bool found=false;
					if(temp.SearchHorizontalLine_(i,-1)==8)  found=true;
					if(temp.SearchVerticalLine_(j,-1)==8)    found=true;
					if(temp.SearchBox_(temp.FindBox_(i,j),-1)==8) found=true;
					if(found)
					{
						x.Write_(i,j,value);
						return 0;
					}
				}
			}
		}

	}
	return -1;
}

//checks each box to see if it only has empty squares on one of its rows or columns
//if it does it tests the squares on that row or col that are not in the box with
//elimination test that also eliminates the values that go in the empty spots in then
//row or column of the box
int BlockLineElimination(SudokuPuzzle &x)
{
	int row_start=0;
	int row_end=0;
	int col_start=0;
	int col_end=0;
	for(int box=0; box<9; box++)
	{
		switch(box)
		{
			case 0: row_start=0; row_end=2; col_start=0; col_end=2; break;
			case 1: row_start=0; row_end=2; col_start=3; col_end=5; break;
			case 2: row_start=0; row_end=2; col_start=6; col_end=8; break;
			case 3: row_start=3; row_end=5; col_start=0; col_end=2; break;
			case 4: row_start=3; row_end=5; col_start=3; col_end=5; break;
			case 5: row_start=3; row_end=5; col_start=6; col_end=8; break;
			case 6: row_start=6; row_end=8; col_start=0; col_end=2; break;
			case 7: row_start=6; row_end=8; col_start=3; col_end=5; break;
			case 8: row_start=6; row_end=8; col_start=6; col_end=8; break;
			default: return -1;
		}
		//scan rows of box for blocked row
		for(int i=row_start; i<=row_end;i++)
		{
			int count=0;
			for(int j=col_start; j<=col_end; j++)
			{
				if(x.Read_(i,j)==0) count++;
			}
			if(count!=0 && count==x.SearchBox_(box,0))
			{
				//BLOCKROW
				for(int col=0; col<9; col++)
				{
					if(col<col_start || col>col_end)
					{//run eliminate with values removed
						int possible_value=0;
						int possible_count=0;
						if(x.Read_(i,col)==0)
						{
							for(int value=1; value<10; value++)
							{
								//test the squares to see if value is possible and that value is not one of the possibles from the  blocked row
								if(x.TestSquare_(i,col,value)==true  && x.SearchBox_(box,value)==1)
								{
									possible_value=value;
									possible_count++;
								}
							}
						}
						if(possible_count==1)
						{
							x.Write_(i,col,possible_value);
							return 0;
						}
					}
				}
			}
		}
		//scan cols of box for blocked cols
		for(int j=col_start; j<=col_end; j++)
		{
			int count=0;
			for(int i=row_start; i<=row_end;i++)
			{
				if(x.Read_(i,j)==0) count++;
			}
			if(count!=0 && count==x.SearchBox_(box,0))
			{
				//BLOCKCOL
				for(int row=0; row<9; row++)
				{
					if(row<row_start || row>row_end)
					{//run eliminate with values removed
						int possible_value=0;
						int possible_count=0;
						if(x.Read_(row,j)==0)
						{
							for(int value=1; value<10; value++)
							{
								//test the squares to see if value is possible and that value is not one of the possibles from the  blocked col
								if(x.TestSquare_(row,j,value)==true  && x.SearchBox_(box,value)==1)
								{
									possible_value=value;
									possible_count++;
								}
							}
						}
						if(possible_count==1)
						{
							x.Write_(row,j,possible_value);
							return 0;
						}
					}
				}
			}
		}
	}
	return -1;
}

//checks each box to see if any of its rows or cols have the only squares in that box
//that can hold any value. when it finds such a row or col it it runs an elimination
//type sweep of the row or col with those values blocked
int BlockLineValueElimination(SudokuPuzzle &x)
{
	int row_start=0;
	int row_end=0;
	int col_start=0;
	int col_end=0;
	for(int box=0; box<9; box++)
	{
		switch(box)
		{
			case 0: row_start=0; row_end=2; col_start=0; col_end=2; break;
			case 1: row_start=0; row_end=2; col_start=3; col_end=5; break;
			case 2: row_start=0; row_end=2; col_start=6; col_end=8; break;
			case 3: row_start=3; row_end=5; col_start=0; col_end=2; break;
			case 4: row_start=3; row_end=5; col_start=3; col_end=5; break;
			case 5: row_start=3; row_end=5; col_start=6; col_end=8; break;
			case 6: row_start=6; row_end=8; col_start=0; col_end=2; break;
			case 7: row_start=6; row_end=8; col_start=3; col_end=5; break;
			case 8: row_start=6; row_end=8; col_start=6; col_end=8; break;
			default: return -1;
		}
		//scan box-row for blocked row
		for(int i=row_start; i<=row_end;i++)
		{
			int value1=0;
			int value2=0;
			int value3=0;
			int value_count=0;
			for(int value=1; value<10; value++)
			{
				int row_count=0;
				int box_count=0;
				for(int j=col_start; j<=col_end ;j++)//count how many squares in box-row could hold value
				{
					if(x.Read_(i,j)==0)
						if(x.TestSquare_(i,j,value))
							row_count++;
				}
				for(int row=row_start; row<=row_end; row++)//count how many squares in box could hold value
				{
					for(int col=col_start; col<=col_end; col++)
					{
						if(x.Read_(row,col)==0)
							if(x.TestSquare_(row,col,value))
								box_count++;
					}
				}
				if(box_count!=0 && box_count==row_count)
				{
					if(value_count==0) {value1=value; value_count++;}
					if(value_count==1) {value2=value; value_count++;}
					if(value_count==2) {value3=value; value_count++;}
				}
			}
			if(value_count>0)
			{
				for(int col=0; col<9; col++)
				{
					if(x.Read_(i,col)==0 && (col<col_start || col>col_end))
					{
						int possible_count=0;
						int possible_value=0;
						for(int value=1; value<10; value++)
						{
							if(value!=value1 && value!=value2 && value!=value3)
							{
								if(x.TestSquare_(i,col,value))
								{
									possible_value=value;
									possible_count++;
								}
							}
						}
						if(possible_count==1)
						{
							x.Write_(i,col,possible_value);
							return 0;
						}
					}
				}
			}
		}//end scan box-row

		//scan box-col for blocked col
		for(int j=col_start; j<=col_end ;j++)
		{
			int value1=0;
			int value2=0;
			int value3=0;
			int value_count=0;
			for(int value=1; value<10; value++)
			{
				int col_count=0;
				int box_count=0;
				for(int i=row_start; i<=row_end;i++)//count how many squares in box-col could hold value
				{
					if(x.Read_(i,j)==0)
						if(x.TestSquare_(i,j,value))
							col_count++;
				}
				for(int row=row_start; row<=row_end; row++)//count how many squares in box could hold value
				{
					for(int col=col_start; col<=col_end; col++)
					{
						if(x.Read_(row,col)==0)
							if(x.TestSquare_(row,col,value))
								box_count++;
					}
				}
				if(box_count!=0 && box_count==col_count)
				{
					if(value_count==0) {value1=value; value_count++;}
					if(value_count==1) {value2=value; value_count++;}
					if(value_count==2) {value3=value; value_count++;}
				}
			}
			if(value_count>0)
			{
				for(int row=0; row<9; row++)
				{
					if(x.Read_(row,j)==0 && (row<row_start || row>row_end))
					{
						int possible_count=0;
						int possible_value=0;
						for(int value=1; value<10; value++)
						{
							if(value!=value1 && value!=value2 && value!=value3)
							{
								if(x.TestSquare_(row,j,value))
								{
									possible_value=value;
									possible_count++;
								}
							}
						}
						if(possible_count==1)
						{
							x.Write_(row,j,possible_value);
							return 0;
						}
					}
				}
			}
		}//end scan box-col

	}//end for:box
	return -1;
}

//for each square checks box,row, and col to eliminate values-writes if one is left
//only finds one per call
int Elimination(SudokuPuzzle &x)
{
	int change=false;
	for(int i=0; i<9; i++)
	{
		for(int j=0; j<9; j++)
		{
			int possible_value=0;
			int possible_count=0;
			if(x.Read_(i,j)==0)
			{
				for(int value=1; value<10; value++)
				{
					if(x.TestSquare_(i,j,value)==true)
					{
						possible_value=value;
						possible_count++;
					}
				}
			}
			if(possible_count==1)
			{
				x.Write_(i,j,possible_value);
				return 0;
			}
		}
	}

	return -1;
}

int Solver(SudokuPuzzle& x)
{
	SudokuPuzzle temp=x;

	while(x.Check_()>0) //no exit until puzzle complete or unsolvable
	{
		bool change=false;

		while(Elimination(temp)==0)
		{
			change=true;
			#if DEBUG
			elimination_counter++;
			#endif
		}

		while(BlockLineElimination(temp)==0)
		{
			change=true;
			#if DEBUG
			valueElimination_counter++;
			#endif
		}

		while(BlockLineValueElimination(temp)==0)
		{
			change=true;
			#if DEBUG
			blockElimination_counter++;
			#endif
		}

		while(OnlyPossible(temp)==0)
		{
			change=true;
			#if DEBUG
			only_counter++;
			#endif
		}

		if(change==false)	//This will recursively guess every possible solution until solved
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
								#if DEBUG
								guess.Display_();
								guess_counter++;
								cout<<"guess: ("<<i<<","<<j<<") = "<<value
										<<"\nguess_counter: "<<guess_counter
										<<"\nonly_counter: "<<only_counter
										<<"\nelimination_counter: "<<elimination_counter
										<<"\nblockElimination_counter: "<<blockElimination_counter
										<<"\nvalueElimination_counter: "<<valueElimination_counter<<"\n";
								#endif
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
		if(temp.Check_()==0){x=temp;return 0;}
	}
	if(temp.Check_()==-1) return -1;
	return 0;
}

SudokuPuzzle SudokuSolver(SudokuPuzzle x)
{
	int squares=x.Check_();

	#if DEBUG
	guess_counter=0;
	only_counter=0;
	elimination_counter=0;
	blockElimination_counter=0;
	valueElimination_counter=0;
	#endif

	Solver(x);

	#if DEBUG
	x.Display_();
	cout<<"guess: "<<guess_counter
			<<"\nonly_counter: "<<only_counter
			<<"\nelimination_counter: "<<elimination_counter
			<<"\nblockElimination_counter: "<<blockElimination_counter<<""
			<<"\nvalueElimination_counter: "<<blockElimination_counter<<"\n";
	#endif

	return x;
}

#endif /* SUDOKU_PUZZLE_H_ */
