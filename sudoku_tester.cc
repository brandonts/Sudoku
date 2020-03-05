/*
 * sudoku_tester.cc
 *
 *  Created on: Sep 18, 2019
 *      Author: Brandon Shaw
 */

#include <iostream>
#include <iomanip>
#include <vector>

#include "sudoku_solver.h"
#include "sudoku_puzzle.h"


using namespace std;

void FormatDisplay(string testName)
{
	cout<<setw(30)<<left<<testName<<":\t";
}

void FormatRight(string description,string status)
{
	cout<<setw(30)<<right<<description<<":\t"<<status<<"\n";
}

int TestEmptyPuzzle()
{
	FormatDisplay("TestEmptyPuzzle()");
	SudokuPuzzle p1{};
	vector<int> expectedResult
	{
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};
	if (p1 == expectedResult) cout<<"Pass\n";
	else {cout<<"Fail\n";return 1;}
	return 0;
}

int TestSpecificPuzzle()
{
	FormatDisplay("TestSpecificPuzzle()");
	vector<int> specificPuzzle
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
	SudokuPuzzle p1{specificPuzzle};
	if (p1==specificPuzzle) cout<<"Pass\n";
	else {cout<<"Fail\n";return 1;}
	return 0;
}

int TestPuzzleValidation()
{
	FormatDisplay("TestPuzzleValidation()");
	vector<int> invalidPuzzle{1,2,3};
	try{SudokuPuzzle p1{invalidPuzzle};cout<<"Fail\n";return 1;
	}catch (invalid_argument e1){cout<<"Pass\n";}
	return 0;
}

int TestWrite_()
{
FormatDisplay("TestWrite_()");
	SudokuPuzzle p1{};
	int testFailures=0;
	cout<<"\n";
	try{p1.Write_(-1,5,2);FormatRight("Invalid Row","Fail");testFailures++;
}catch (invalid_argument e1){FormatRight("Invalid Row","Pass");}

	try{p1.Write_(5,9,2);FormatRight("Invalid Column","Fail");testFailures++;
}catch (invalid_argument e1){FormatRight("Invalid Column","Pass");}

	try{p1.Write_(5,5,10);FormatRight("Invalid Value","Fail");testFailures++;
}catch (invalid_argument e1){FormatRight("Invalid Value","Pass");}
	if(testFailures>0)return testFailures;
	return 0;
}

int TestRead_()
{
	FormatDisplay("TestRead_()");
	SudokuPuzzle p1{};
	int testFailures=0;
	cout<<"\n";
	try{p1.Read_(-1,5);FormatRight("Invalid Row","Fail");testFailures++;
}catch (invalid_argument e1){FormatRight("Invalid Row","Pass");}

	try{p1.Read_(6,9);FormatRight("Invalid Column","Fail");testFailures++;
}catch (invalid_argument e1){FormatRight("Invalid Column","Pass");}

	if(testFailures>0)return testFailures;
	return 0;
}

int TestCheck_()
{
	FormatDisplay("TestCheck_()");
	int testFailures=0;
	SudokuPuzzle p1{};
	if(p1.Check_()!=81)testFailures++;

	vector<int> badPuzzle
	{
		1,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};
	try{p1=badPuzzle;testFailures++;
	}catch(invalid_argument e1){}

	badPuzzle=
	{
		1,0,0,0,0,0,0,0,1,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0
	};
	try{p1=badPuzzle;testFailures++;
	}catch(invalid_argument e1){}

	badPuzzle=
	{
		0,0,0,0,6,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,6,0,0,0,0
	};
	try{p1=badPuzzle;testFailures++;
	}catch(invalid_argument e1){}

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int TestSearchBox()
{
	FormatDisplay("TestSearchBox()");
	int testFailures=0;

	SudokuPuzzle p1{};
	if(p1.SearchBox_(0,1)!=0)testFailures++;

	p1.Write_(0,0,1);
	p1.Write_(0,1,1);
	if(p1.SearchBox_(0,1)!=2)testFailures++;
	p1.Write_(1,1,1);
	if(p1.SearchBox_(0,1)!=3)testFailures++;

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int TestSearchVerticalLine()
{
	FormatDisplay("TestSearchVerticalLine()");
	int testFailures=0;

	SudokuPuzzle p1{};
	if(p1.SearchVerticalLine_(0,6)!=0)testFailures++;

	p1.Write_(1,0,6);
	p1.Write_(2,0,6);
	if(p1.SearchVerticalLine_(0,6)!=2)testFailures++;
	p1.Write_(3,0,6);
	if(p1.SearchVerticalLine_(0,6)!=3)testFailures++;

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int TestSearchHorizontalLine()
{
	FormatDisplay("TestSearchHorizontalLine()");
	int testFailures=0;

	SudokuPuzzle p1{};
	if(p1.SearchHorizontalLine_(0,6)!=0)testFailures++;

	p1.Write_(0,1,6);
	p1.Write_(0,4,6);
	if(p1.SearchHorizontalLine_(0,6)!=2)testFailures++;
	p1.Write_(0,8,6);
	if(p1.SearchHorizontalLine_(0,6)!=3)testFailures++;

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int TestFindBox()
{
	int testFailures=0;
	FormatDisplay("TestFindBox()");
	vector<int> specificPuzzle
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
	SudokuPuzzle p1{specificPuzzle};
	if(p1.FindBox_(0,0)!=0)testFailures++;
	if(p1.FindBox_(1,4)!=1)testFailures++;
	if(p1.FindBox_(2,8)!=2)testFailures++;
	if(p1.FindBox_(4,1)!=3)testFailures++;
	if(p1.FindBox_(5,5)!=4)testFailures++;
	if(p1.FindBox_(5,6)!=5)testFailures++;
	if(p1.FindBox_(8,1)!=6)testFailures++;
	if(p1.FindBox_(7,5)!=7)testFailures++;
	if(p1.FindBox_(8,6)!=8)testFailures++;

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int TestTestSquare()
{
	int testFailures=0;
	FormatDisplay("TestTestSquare()");
	vector<int> specificPuzzle
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
	SudokuPuzzle p1{specificPuzzle};
	if(p1.TestSquare_(0,0,3)!=false)testFailures++;
	if(p1.TestSquare_(1,4,8)!=true)testFailures++;
	if(p1.TestSquare_(2,8,9)!=false)testFailures++;
	if(p1.TestSquare_(4,1,1)!=false)testFailures++;
	if(p1.TestSquare_(5,5,8)!=false)testFailures++;
	if(p1.TestSquare_(5,6,5)!=true)testFailures++;
	if(p1.TestSquare_(7,3,3)!=true)testFailures++;

	if(testFailures>0){cout<<"Fail\n";return 1;}
	cout<<"Pass\n";
	return 0;
}

int IsPuzzleCorrupted(SudokuPuzzle p1, SudokuPuzzle p2)//returns number of corrupted squares
{
	int corruptedPuzzleCount=0;
	for(int i=0;i<9;i++)//cycle through all squares on puzzle and make sure origonal numbers didn't get changed
	{
			for(int j=0;j<9;j++)
			{
				if(p1.Read_(i,j)!=0)
					{
						if(p1.Read_(i,j)!=p2.Read_(i,j))corruptedPuzzleCount++;
						//cout<<"p1("<<i<<","<<j<<") = "<<p1.Read_(i,j);
						//cout<<"\tp2("<<i<<","<<j<<") = "<<p2.Read_(i,j)<<"\n";
					}
			}
	}
	return corruptedPuzzleCount;
}

int TestSudokuSolver()
{
	FormatDisplay("TestSudokuSolver()");
	cout<<"\n";
	int testFailures=0;
	vector<int> specificPuzzle
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
	SudokuPuzzle p1{specificPuzzle};

	//test that SudokuSolver did not corrupt puzzle
	SudokuPuzzle p2=SudokuSolver(p1);
	int corruptedPuzzleCount=IsPuzzleCorrupted(p1,p2);
	if(corruptedPuzzleCount>0)
	{
		FormatRight("PuzzleNotCorrupted","Fail");
		testFailures++;
	}else FormatRight("PuzzleNotCorrupted","Pass");

	//test that IsPuzzleCorrupt catches corrupted puzzle
	p2=p1;
	p2.Write_(0,2,6);
	corruptedPuzzleCount=IsPuzzleCorrupted(p1,p2);
	if(corruptedPuzzleCount==0)
	{
		FormatRight("CatchPuzzleCorrupted","Fail");
		testFailures++;
	}else FormatRight("CatchPuzzleCorrupted","Pass");

	//test that SudokuSover returns a valid puzzle solution
	p2=SudokuSolver(p1);
	if(p2.Check_()==-1){FormatRight("ValidSolutionReturned","Fail-Invalid");testFailures++;}
	if(p2.Check_()>0){FormatRight("ValidSolutionReturned","Fail-Not Complete");testFailures++;}
	if(p2.Check_()==0)FormatRight("ValidSolutionReturned","Pass");

	return testFailures;
}

int main()
{
	//sudoku_puzzle.h tests
	cout<<"Testing sudoku_puzzle.h:\n";
	int testFailures =0;
	testFailures+=TestEmptyPuzzle();
	testFailures+=TestSpecificPuzzle();
	testFailures+=TestPuzzleValidation();
	testFailures+=TestWrite_();
	testFailures+=TestRead_();
	testFailures+=TestCheck_();
	testFailures+=TestSearchBox();
	testFailures+=TestSearchVerticalLine();
	testFailures+=TestSearchHorizontalLine();
	testFailures+=TestFindBox();
	testFailures+=TestTestSquare();

	int puzzleTestFailures=testFailures;

	//sudoku_solver.h tests
	cout<<"\nTesting sudoku_solver.h:\n";
	testFailures=0;

	//testFailures+=TestOnlyPossible();

	testFailures+=TestSudokuSolver();

	int solverTestFailures=testFailures;

	if(puzzleTestFailures==0)cout<<"\nsudoku_puzzle.h passed all tests!\n";
	else cout<<"sudoku_puzzle.h failed "<<puzzleTestFailures<<" tests.\n";

	if(solverTestFailures==0)cout<<"sudoku_solver.h passed all tests!\n";
	else cout<<"sudoku_solver.h failed "<<solverTestFailures<<" tests.\n";

	return 0;
}
