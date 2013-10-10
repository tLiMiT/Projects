// Tim Liming
// 5 Dec 2012
//
// The program file for dice project
// Contains the main function

#include "dice.h"

using namespace std;

int main()
{
	// initialize variables
	int num, roll1, roll2;
	float ones = 0, twos = 0, threes = 0, fours = 0, fives = 0, sixes = 0;

	// get the number of rolls
	cout << "Enter the number of rolls: ";
	cin >> num;
	cout << endl;

	// handle rolling the dice
	for (int i = 0; i < num; i++)
	{
		// roll dice
		roll1 = randDie();
		roll2 = randDie();

		// record rolls
		if (roll1 == 1) { ones++; }
		else if (roll1 == 2) { twos++; }
		else if (roll1 == 3) { threes++; }
		else if (roll1 == 4) { fours++; }
		else if (roll1 == 5) { fives++; }
		else if (roll1 == 6) { sixes++; }
		
		if (roll2 == 1) { ones++; }
		else if (roll2 == 2) { twos++; }
		else if (roll2 == 3) { threes++; }
		else if (roll2 == 4) { fours++; }
		else if (roll2 == 5) { fives++; }
		else if (roll2 == 6) { sixes++; }
		
	} // for

	// print roll results
	cout << "Rolls of 1: " << ones << endl;
	cout << "Rolls of 2: " << twos << endl;
	cout << "Rolls of 3: " << threes << endl;
	cout << "Rolls of 4: " << fours << endl;
	cout << "Rolls of 5: " << fives << endl;
	cout << "Rolls of 6: " << sixes << endl;
	cout << endl;

	// percentage distribution
	cout << "Percentage of 1: " << (ones/num)*100 << "%" << endl;
	cout << "Percentage of 2: " << (twos/num)*100 << "%" << endl;
	cout << "Percentage of 3: " << (threes/num)*100 << "%" << endl;
	cout << "Percentage of 4: " << (fours/num)*100 << "%" << endl;
	cout << "Percentage of 5: " << (fives/num)*100 << "%" << endl;
	cout << "Percentage of 6: " << (sixes/num)*100 << "%" << endl;
	cout << endl;

	system("PAUSE");
	return 0;
}