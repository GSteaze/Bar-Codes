#include <iostream>
#include <fstream>
#include <string>

#include "BarCodes.h"

using namespace std;
using namespace barcodes;

int main()
{
	bool isAgain = 0;

	do
	{
		string userInput = UserInput();
		Converter(userInput);
		isAgain = RunItAgain();

	} while (isAgain);

	//TestCode();
	return 0;
}