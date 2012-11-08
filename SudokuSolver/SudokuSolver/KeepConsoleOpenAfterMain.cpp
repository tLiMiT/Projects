// Prevents console from closing after main has completed

#include <iostream>

using namespace std;

class KeepConsoleOpenAfterMain 
{
public:
    ~KeepConsoleOpenAfterMain() 
	{
        cout << "\nPress Enter to close... ";
        cin.clear();
        cin.sync();
        cin.ignore();
    }
} keepConsoleOpenAfterMain;
