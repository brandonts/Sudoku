 // sudoku_puzzle.h

#ifndef SUDOKU_PUZZLE_H_
#define SUDOKU_PUZZLE_H_

#include <vector>

class SudokuPuzzle
{
private:
	std::vector<int> table;

	public:
		void Display_();
		SudokuPuzzle();
		SudokuPuzzle(std::vector<int> v);
		bool operator==(const SudokuPuzzle &other);
		bool operator==(const std::vector<int> &other);
		bool operator!=(const std::vector<int> &other);
		void Write_(int row, int column, int value);//writes value to a square
		int Read_(int row, int column) const;//reads value from a square
		int Check_();//returns -1 if puzzle has become inconsistent, returns the number of empty square otherwise
		int SearchBox_(int box_number,int search_value);//returns how many times a search_value is found in a box
		int SearchVerticalLine_(int line_number,int search_value);//returns how many times a search_value is found in a column
		int SearchHorizontalLine_(int line_number,int search_value);//returns how many times a search_value is found in a row
		bool TestSquare_(int row, int column, int search_value);//returns true when square could hold search_value withought makeing the puzzle inconsistent
		int FindBox_(int row,int column);//returns index of box that a square(0-80))is in
		std::vector<int> GetPuzzle_();
		//friend void ncurse::WriteFile(const SudokuPuzzle &p1, string file);
};
#endif /* SUDOKU_PUZZLE_H_ */
