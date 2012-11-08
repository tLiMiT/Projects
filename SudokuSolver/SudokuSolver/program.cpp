// SudokuSolver
//
// Tim Liming
//

#include <iostream>

using namespace std;


// MAIN FUNCTION
int main()
{
	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "sudoku.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		time_t start, end;
		double diff;
		time (&start);

		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			numBoards++;

			b1.clearCount();		// clear count for new round

			b1.initialize(fin);

			for (int i = 0; i < 9; i++) 
			{ 
				for (int j = 0; j < 9; j++) 
				{ 
					outputArray[i][j] = array[i][j]; 
				} // for
			} // for 

			cout << "\nSolving Board " << numBoards << "..." << endl;
			b1.print();				// print loaded board

			// solve the sudoku board
			if (b1.backtrack(0, 0))
			{
				b1.printArray();	// print the solved board
			} // if

			cout << "Number of calls: " << b1.getCount() << endl;
			totalCalls += b1.getCount();
			
		} // while

		cout << "Average number of calls: " << totalCalls / numBoards << endl;
		
		time (&end);
		diff = difftime(end, start);
		printf("Runtime: %.2f minutes.\n", diff/60);
	} // try
	catch  (rangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
} // main