/*
 * Sudoku_Puzzle.h
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#ifndef SUDOKU_PUZZLE_H_
#define SUDOKU_PUZZLE_H_

#include <iostream>
#include <vector>

using namespace std;

class SudokuPuzzle
{
	private:
		vector<int> table;

	public:
		SudokuPuzzle(vector<int> v);
		SudokuPuzzle();
		int Check_();
		void Display_();
		void Write_(int row, int column, int value);
		int Read_(int row, int column);
		int SearchBox_(int box_number,int search_value);
		int SearchVerticalLine_(int line_number,int search_value);
		int SearchHorizontalLine_(int line_number,int search_value);
		int FindVerticalLine_(int square);
		int FindHorizontalLine_(int square);
		int FindBox_(int square);
		bool TestSquare_(int row, int column, int search_value);// need to check if it works
};

SudokuPuzzle::SudokuPuzzle(vector<int> v)
{
	if(v.size()!=81) throw invalid_argument("SudokuPuzzle::SudokuPuzzle: vector not size 81");
	table=v;
	if(Check_()==-1) throw invalid_argument("SudokuPuzzle::SudokuPuzzle: invalid configuration");
}

SudokuPuzzle::SudokuPuzzle()
{
	for(int i=0; i<81; i++) table.push_back(0);
}

void SudokuPuzzle::Display_()
{
	cout << "\n";
	for(int i=0;i<9;i++)
	{
		if(i==0 || i==3 || i==6) cout<<"\n-------------------\n";
		else cout<<"\n";
		cout << "|";
		for(int j=0;j<9;j++)
		{
			cout << table[i*9+j];
			if(j==2 || j==5 || j==8) cout<<"|";
			else cout<<" ";
		}
	}
	 cout<<"\n-------------------\n";
}

void SudokuPuzzle::Write_(int row, int column, int value)
{
	int square=(row*9+column);
	if(square>80) throw invalid_argument("SudokuPuzzle::Write_: out of bounds 0-80 required");
	table[square]=value;
}

int SudokuPuzzle::Read_(int row, int column)
{
	return table[row*9+column];
}

int SudokuPuzzle::Check_()
{
	for(int i=0; i<9; i++)
	{
		for(int j=1; j<10; j++)
		{
			if(SearchBox_(i,j)>1) 			return(-1);
			if(SearchVerticalLine_(i,j)>1) 	return(-1);
			if(SearchHorizontalLine_(i,j)>1)return(-1);
		}
	}
	int empty_squares=0;
	for(int i=0; i<81; i++) if(table[i]==0) empty_squares++;
	return empty_squares;
}

int SudokuPuzzle::SearchBox_(int box_number,int search_value)
{
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
	for(int i=line_number; i<8; i=+9) if(table[i]==search_value) count++;

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

int SudokuPuzzle::FindVerticalLine_(int square)
{
	if(square<0 || square>80) throw invalid_argument("SudokuPuzzle::FindVerticalLine_: out of bounds 0-80 required");
	while(square>8) square-=9;

	return square;
}

int SudokuPuzzle::FindHorizontalLine_(int square)
{
	if(square<0 || square>80) throw invalid_argument("SudokuPuzzle::FindHorizontalLine_: out of bounds 0-80 requried");
	int count=0;
	while(square>8) count++;

	return count;
}

int SudokuPuzzle::FindBox_(int square)
{
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

bool SudokuPuzzle::TestSquare_(int row, int column, int value)
{
	int square=row*9+column;
	return (!(this->SearchBox_(this->FindBox_(square),value) &&
			!this->SearchVerticalLine_(this->FindVerticalLine_(square),value) &&
			!this->SearchHorizontalLine_(this->FindHorizontalLine_(square),value)));
}

#endif /* SUDOKU_PUZZLE_H_ */
