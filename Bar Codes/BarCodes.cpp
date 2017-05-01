#include <iostream>
#include <fstream>
#include <string>

#include "BarCodes.h"

using namespace std;

const int kEndOfLine = 1024;

namespace barcodes
{
	/*
	Prompts user to enter the zip code or bar code and takes input

	@return Zip
	*/
	string UserInput()
	{
		string userInput = " ";
		cout << "Enter bar code or Zip Code:";
		cin >> userInput;
		userInput = InvalidInput(userInput);
		return userInput;
	}

	/*
	Checks to see if the user input is valid

	@param userInput the input from the user

	@return validInput
	*/
	string InvalidInput(string userInput)
	{
		bool isNeither = (userInput[0] != ':') && (userInput[0] != '|') && ((userInput[0] < '0') || (userInput[0] > '9'));
		while (isNeither)
			{
				cout << "Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				userInput = InvalidInput(userInput);
				isNeither = ((userInput[0] != ':' || userInput[0] != '|') && (userInput[0] < '0' && userInput[0] > '9'));
			}
		if (userInput[0] == ':' || userInput[0] == '|')
		{
			bool isValidBarCode = BarCodeValidator(userInput);
			while (!isValidBarCode)
			{
				cout << "Bar code can only contain : and |. Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				isValidBarCode = BarCodeValidator(userInput);
			}
			if (isValidBarCode)
			{
				return userInput;
			}
		}
		if (userInput[0] >= '0' && userInput[0] <= '9')
		{
			bool isValidZipCode = ZipCodeValidator(userInput);
			while (!isValidZipCode)
			{
				cout << "Zip code can only contain numbers and must be 5 digits long" << endl
					<< "Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				isValidZipCode = BarCodeValidator(userInput);
			}
			if (isValidZipCode)
			{
				return userInput;
			}
		}
	}

	/*
	Checks to see if the bar code is valid

	@param barCode the bar code to be tested

	@return validBarCode
	*/
	bool BarCodeValidator(string barCode)
	{
		bool isValidBarCode = 1;
		for (int index = 0; index < barCode.size(); index++)
		{
			if (barCode[index] != ':' && barCode[index] != '|')
			{
				return isValidBarCode = 0;
			}
		}
		return isValidBarCode;
	}

	/*
	Checks to see if the zip code is valid

	@param zipCode the zip code to be tested
	@param &isValidZipCode is true if the bar code is the proper size and only contains numbers
	*/
	bool ZipCodeValidator(string zipCode)
	{	
		bool isValidZipCode = 1;
		if (zipCode.size() != 5)
		{
			isValidZipCode = 0;
		}
		for (int index = 0; index < zipCode.size(); index++)
		{
			if (zipCode[index] < '0' || zipCode[index] > '9')
			{
				isValidZipCode = 0;
			}
		}
		return isValidZipCode;
	}

	void TestCode()
	{
		//BarCodeValidator
		bool isValidBarCode = 1;
		isValidBarCode = BarCodeValidator(":||||:");
		cout << isValidBarCode << endl;
		isValidBarCode = BarCodeValidator("9");
		cout << isValidBarCode << endl;
		isValidBarCode = BarCodeValidator("|:9");
		cout << isValidBarCode << endl;
		
		//ZipCodeValidator
		bool isValidZipCode = 1;
		isValidZipCode = ZipCodeValidator("72762");
		cout << isValidZipCode << endl;
		return;
	}
};