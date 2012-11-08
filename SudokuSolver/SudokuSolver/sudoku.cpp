// SudokuSolver
//
// Tim Liming
//

#include "sudoku.h"

typedef int ValueType;		// The type of the value in a cell
const int Blank = -1;		// Indicates that a cell is blank

const int SquareSize = 3;	//  The number of cells in a small square
							//  (usually 3).  The board has
							//  SquareSize^2 rows and SquareSize^2
							//  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

int totalCalls = 0;
int numBoards = 0;

int array[9][9]; 
int outputArray[9][9]; 


board::board(int sqSize)
	: value(BoardSize+1, BoardSize+1),
	rows(BoardSize+1, BoardSize+1),
	cols(BoardSize+1, BoardSize+1),
	sqrs(BoardSize+1, BoardSize+1)
	// Board constructor
{
}

void board::clearCell(int i, int j)
	// clear a cell in the sudoku board
{
	updateConflicts(i, j, value[i][j], 0);
	value[i][j] = 0;
} // clearCell

void board::clear()
	// clear the sudoku board
{
	for (int i = 1; i < value.rows(); i++)
	{
		for (int j = 1; j < value.cols(); j++)
		{
			clearCell(i, j);
		} // for
	} // for
} // clear

void board::initialize(ifstream &fin)
	// Read a Sudoku board from the input file.
{
	char ch;

	clear();	// clear incase there is a board already loaded

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
			{
				if (conflicts(i, j, ch-'0'))
				{
					throw rangeError("conflict on initialization");
				}
				setCell(i, j, ch-'0');	// Convert char to int
				array[i-1][j-1] = ch-'0';
			} 
			else if (ch == '.')
			{
				setCell(i, j, 0);		// set cell to 0
				array[i-1][j-1] = 0;
			}// if - else if
		} // for
	} // for
} // initialize

int squareNumber(int i, int j)
	// Return the square number of cell i,j (counting from left to right,
	// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.  

	return SquareSize * ((i-1)/SquareSize) + (j-1)/SquareSize + 1;
}

bool board::conflicts(int i, int j, int val)
	// check the row, column, and square for conflicts of a given value
{
	return rows[i][val] || cols[j][val] || sqrs[squareNumber(i, j)][val];
} // conflicts

void board::updateConflicts(int i, int j, int num, bool val)
	// update each of the three possible conflict areas
{
	rows[i][num] = val;
	cols[j][num] = val;
	sqrs[squareNumber(i, j)][num] = val;
} // updateConflicts

ostream &operator<<(ostream &ostr, vector<int> &v)
	// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
	{
		ostr << v[i] << " ";
	}
	ostr << endl;
	return ostr;
}

ValueType board::getCell(int i, int j)
	// Returns the value stored in a cell.  Throws an exception
	// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
	{
		return value[i][j];
	}
	else
	{
		throw rangeError("bad value in getCell");
	}
} // getCell

void board::setCell(int i, int j, int val)
	// set the value of the cell
{
	value[i][j] = val;
	updateConflicts(i, j, val, true);
} // setCell

bool board::isBlank(int i, int j)
	// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
	{
		throw rangeError("bad value in setCell");
	}
	else
	{
		return value[i][j] == 0;
	}
} // isBlank

bool board::solvedBoard()
	// check if the sudoku board is solved
{
	for (int i = 1; i < BoardSize; i++)
	{
		for (int j = 1; j < BoardSize; j++)
		{
			if (isBlank(i,j))
			{
				return false;
			} // if
		} // for
	} // for
	return true;
} // solvedBoard

int board::findBestBlank(int &x, int &y)
	// find a blank spot in the sudoku puzzle
	// returns a pair of ints that are the indices in the board
	// that have the least amount of possible choices
{
	int maxConflicts = MaxValue;
	int temp;

	for (int i = MinValue; i <= MaxValue; i++)
	{
		for (int j = MinValue; j <= MaxValue; j++)
		{
			if (! isBlank(i, j)) { continue; }
			temp = MaxValue;
			for (int x = MinValue; x <= MaxValue; x++)
			{
				temp -= (rows[i][x] == 1); 
				temp -= (cols[j][x] == 1); 
				temp -= (sqrs[squareNumber(i, j)][x] == 1);
			} // for

			if (temp <= maxConflicts)
			{
				maxConflicts = temp;
				x = i;
				y = j;
			} // if
		} // for
	} // for
	return maxConflicts;
} // findBestBlank

bool board::solve(int i, int j)
	// solve the sudoku board using recursion
{
	numRecursions++;	// increase the count every time solve() is called
	
	// initialize indices
	int i1;
	int j1;

	// loop through numbers 1-9
	for (int num = MaxValue; num >= MinValue; num--)
	{
		// if there are no conflicts
		if (! conflicts(i, j, num))
		{
			setCell(i, j, num);		// set cell as that number

			if (solvedBoard()) { return true; }

			findBestBlank(i1, j1);	// find next best position

			if (solve(i1, j1))		// recursion
			{
				return true;
			} // if
			else
			{
				clearCell(i,j);		// clear current cell of number
				continue;
			} // else
		} // if
	} // for
	return false;
} // solve

bool board::boardSolve()
	// handles solving the sudoku board
{
	int i;
	int j;
	findBestBlank(i, j);
	return solve(i, j);
} // boardSolve

int board::input_value(int i, int j, int value)
	// does the heavy lifting for backtrack
{
	for (int k = 0; k < 9; k++)
	{
		if (outputArray[k][j] == value || outputArray[i][k] == value)
		{
			return 0;
		} // if
	} // for

	int newi = (i / 3) * 3;
	int newj = (j / 3) * 3;

	for (int x = newi; x < newi+3; x++)
	{
		for (int y = newj; y < newj+3; y++)
		{
			if (outputArray[x][y] == value)
			{
				return 0;
			} // if
		} // for
	} // for

	return value;
} // input_value

int board::backtrack(int x, int y)
	// solves the board using recursion
	// ( uses ARRAY not MATRIX )
{ 
	numRecursions++;	// increase the count every time backtrack() is called
	int i;

	if (outputArray[x][y] == 0) 
	{ 
		for (i = 1; i < 10; i++) 
		{ 
			int temp = input_value(x, y, i); 

			if (temp > 0) 
			{ 
				outputArray[x][y] = temp; 

				if (x == 8 && y == 8) { return 1; } 
				else if (x == 8) 
				{ 
					if (backtrack(0, y+1)) { return 1; }
				} 
				else 
				{ 
					if (backtrack(x+1, y)) { return 1; }
				} 
			} // if
		} // for

		if (i == 10) 
		{ 
			if (outputArray[x][y] != array[x][y]) 
			{
				outputArray[x][y] = 0;
			}
			return 0; 
		} // if
	} // if
	else 
	{ 
		if (x == 8 && y == 8) { return 1; } 
		else if (x == 8) 
		{    
			if (backtrack(0, y+1)) { return 1; }
		} 
		else 
		{ 
			if (backtrack(x+1, y)) { return 1; }
		} 
	} // else
} // backtrack

void board::print()
	// Prints the current board.
{
	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	}
	cout << "-+";
	cout << endl;

	for (int i = 1; i <= BoardSize; i++)
	{
		if (i == 4 || i == 7)
		{
			cout << "|";
			for (int j = 1; j < SquareSize; j++)
			{
				cout << "---------+";
			}
			cout << "---------|";
			cout << endl;
		} // if

		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j-1) % SquareSize == 0)
			{
				cout << "|";
			}
			if (! isBlank(i, j))
			{
				cout << " " << getCell(i, j) << " ";
			}
			else if (isBlank(i, j))
			{
				cout << "   ";
			}
		} // for
		cout << "|";
		cout << endl;
	} // for

	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	} // for
	cout << "-+";
	cout << endl;
} // print

void board::printArray()
	// Prints the current board from the output array
{
	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	}
	cout << "-+";
	cout << endl;

	for (int i = 1; i <= BoardSize; i++)
	{
		if (i == 4 || i == 7)
		{
			cout << "|";
			for (int j = 1; j < SquareSize; j++)
			{
				cout << "---------+";
			}
			cout << "---------|";
			cout << endl;
		} // if

		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j-1) % SquareSize == 0)
			{
				cout << "|";
			}
			cout << " " << outputArray[i-1][j-1] << " ";
		} // for
		cout << "|";
		cout << endl;
	} // for

	cout << "+-";
	for (int j = 1; j <= BoardSize; j++)
	{
		cout << "---";
	} // for
	cout << "-+";
	cout << endl;
} // print

void board::printConflicts()
	// print each of the conflict matrices side by side
{
	// prints titles spaced correctly
	cout << "Row Conflicts        ";
	cout << "Column Conflicts      ";
	cout << "Square Conflicts" << endl;

	for (int i = 1; i < value.rows(); i++)
	{
		for (int j = 1; j < value.cols(); j++)
		{
			// print a row matrix row
			cout << rows[i][j] << ' ';
		}
		cout << "   ";		// add space between each matrix
		for (int j = 1; j < value.cols(); j++)
		{
			// print a column matrix row
			cout << cols[i][j] << ' ';
		}
		cout << "    ";		// add space between each matrix
		for (int j = 1; j < value.cols(); j++)
		{
			// print a square matrix row
			cout << sqrs[i][j] << ' ';
		}
		cout << endl;		// move to the next line
	} // for
} // printConflicts