#include <iostream>
#include <fstream>
#include <string>

#include "BarCodes.h"

using namespace std;
using namespace barcodes;

int main()
{
	string userInput = UserInput();
	cout << userInput << endl;

	//TestCode();
	return 0;
}