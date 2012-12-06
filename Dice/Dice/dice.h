// Tim Liming
// 5 Dec 2012
//
// The header file for dice project
// Contains function randDie

#include <iostream>
#include <ctime>

using namespace std;

int randDie()
	// generates a random number using ctime
{
	// seed using ctime
	srand(time(NULL) + rand());

	// gets a random number between 1 and 6
	int num = (rand() % 6) + 1;

	// return dice roll
	return num;

} // randDie