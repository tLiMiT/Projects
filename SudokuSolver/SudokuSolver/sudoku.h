// SudokuSolver
//
// Tim Liming
//

#include <iostream>
#include <limits.h>
#include <list>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	ValueType getCell(int, int);

	// Added functions
	void printConflicts();
	bool conflicts(int i, int j, int val);
	void setCell(int i, int j, int val);
	void clearCell(int i, int j);
	bool solvedBoard();
	int getCount() { return numRecursions; }
	void clearCount() { numRecursions = 0; }
	// 4b
	bool boardSolve();
	int input_value(int i, int j, int value);
	int backtrack(int x, int y);
	void printArray();
private:
	// Added functions
	void updateConflicts(int i, int j, int num, bool val);
	int findBestBlank(int &i, int &j);
	bool solve(int i, int j);

	// The following matrices go from 1 to BoardSize in each
	// dimension.  ie. they are each (BoardSize+1)x(BoardSize+1)
	matrix<ValueType> value;

	matrix<bool> rows;		// matrix of each row conflict
	matrix<bool> cols;		// matrix of each column conflict
	matrix<bool> sqrs;		// matrix of each square conflict

	matrix<int> output;		// output matrix

	int numRecursions;
};