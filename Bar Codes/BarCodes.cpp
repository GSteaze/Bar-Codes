#include <iostream>
#include <fstream>
#include <string>

#include "BarCodes.h"

using namespace std;

const int kEndOfLine = 1024;
const int kLengthOfZipCode = 5;
const int kLengthOfBarCode = 32;
const int kNumberOfBarsPerDigit = 5;

namespace barcodes
{
	/*
	Prompts user to enter the zip code or bar code and takes input

	@return Zip
	*/
	string UserInput()
	{
		string userInput = " ";
		cout << "Enter Bar Code or Zip Code:";
		cin >> userInput;
		userInput = InputValidater(userInput);
		return userInput;
	}

	/*
	Checks to see if the user input is valid

	@param userInput the input from the user

	@return validInput
	*/
	string InputValidater(string userInput)
	{
		bool isNeither = (userInput[0] != ':') && (userInput[0] != '|') && ((userInput[0] < '0') || (userInput[0] > '9'));
		while (isNeither)
			{
				cout << "Must be Bar Code or Zip Code" << endl << "Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				isNeither = (userInput[0] != ':') && (userInput[0] != '|') && ((userInput[0] < '0') || (userInput[0] > '9'));
			}
		if (userInput[0] == ':' || userInput[0] == '|')
		{
			bool isValidBarCode = BarCodeValidator(userInput);
			while (!isValidBarCode)
			{
				cout << "Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				isValidBarCode = BarCodeValidator(userInput);
			}
			if (isValidBarCode)
			{
				cout << "Bar Code : " << userInput << endl;
				return userInput;
			}
		}
		if (userInput[0] >= '0' && userInput[0] <= '9')
		{
			bool isValidZipCode = ZipCodeValidator(userInput);
			while (!isValidZipCode)
			{
				cout << "Please try again : ";
				cin.clear();
				cin.ignore(kEndOfLine, '\n');
				cin >> userInput;
				isValidZipCode = ZipCodeValidator(userInput);
			}
			if (isValidZipCode)
			{
				cout << "Zip Code : " << userInput << endl;
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
		if (barCode.size() != kLengthOfBarCode)
		{
			cout << "Invalid Size" << endl;
			return isValidBarCode = 0;
		}
		for (int index = 0; index < barCode.size(); index++)
		{
			if (barCode[index] != ':' && barCode[index] != '|')
			{
				cout << "Bar code can only contain : and |." << endl;
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
		if (zipCode.size() != kLengthOfZipCode)
		{
			cout << "Zip code must be 5 digits long" << endl;
			return isValidZipCode = 0;
		}
		for (int index = 0; index < zipCode.size(); index++)
		{
			if (zipCode[index] < '0' || zipCode[index] > '9')
			{
				cout << "Zip code can only contain numbers." << endl;
				return isValidZipCode = 0;
			}
		}
		return isValidZipCode;
	}

	/*
	Converts the user provided zip code into a bar code

	@param zipCode the zip code entered by the user

	@return barCode the bar code that represents the zip code
	*/
	string ZipCodeToBarCodeConverter(string zipCode)
	{
		string checkDigit = IntegerToStringConversion(CheckDigit(zipCode));
		zipCode.append(checkDigit);
		string barCode = "";
		string frameBars = "|";
		barCode.append(frameBars);
		string digit = "";
		for (int index = 0; index < kLengthOfZipCode + 1; index++)
		{
			if (zipCode[index] == '1')
			{
				digit = ":::||";
			}
			else if (zipCode[index] == '2')
			{
				digit = "::|:|";
			}
			else if (zipCode[index] == '3')
			{
				digit = "::||:";
			}
			else if (zipCode[index] == '4')
			{
				digit = ":|::|";
			}
			else if (zipCode[index] == '5')
			{
				digit = ":|:|:";
			}
			else if (zipCode[index] == '6')
			{
				digit = ":||::";
			}
			else if (zipCode[index] == '7')
			{
				digit = "|:::|";
			}
			else if (zipCode[index] == '8')
			{
				digit = "|::|:";
			}
			else if (zipCode[index] == '9')
			{
				digit = "|:|::";
			}
			else if (zipCode[index] == '0')
			{
				digit = "||:::";
			}
			else
			{
				digit = "invalid";
			}
			barCode.append(digit);
		}
		barCode.append(frameBars);
		return barCode;
	}

	/*
	Converts the user provided bar code into a zip code

	@param barCode the bar code entered by the user

	@return zipCode the zip code that represents the bar code
	*/
	int BarCodeToZipCodeConverter(string barCode)
	{
		string copyOfBarCode = barCode.substr(1, kLengthOfBarCode);
		copyOfBarCode.erase((copyOfBarCode.size() - 1), 1);
		string digit = copyOfBarCode.substr(0, kNumberOfBarsPerDigit);
		int barCodeOnesAndZeros[5];
		int zipCode = 0;
		int number = 0;

		for (int index = 0; index < (copyOfBarCode.size() - kNumberOfBarsPerDigit); index++)
		{
			if ((index + 1) % kNumberOfBarsPerDigit == 0)
			{
				number = (barCodeOnesAndZeros[0] * 7) + (barCodeOnesAndZeros[1] * 4) + (barCodeOnesAndZeros[2] * 2) + (barCodeOnesAndZeros[3] * 1);
				if (number == 11)
				{
					number = 0;
				}
				zipCode = (zipCode * 10) + number;
				digit = copyOfBarCode.substr((index + 1), kNumberOfBarsPerDigit);
			}
			for (int index = 0; index < kNumberOfBarsPerDigit; index++)
			{
				if (digit[index] == ':')
				{
					barCodeOnesAndZeros[index] = 0;
				}
				else if (digit[index] == '|')
				{
					barCodeOnesAndZeros[index] = 1;
				}
			}
		}
		return zipCode;
	}

	/*
	Converts string zip codes into integer zip codes and calculates check digit

	@param zipCodeString the zip code in string form

	@return zipCodeCheckDigit the check digit in integer form
	*/
	int CheckDigit(string zipCodeString)
	{
		int zipCodeInteger = 0;
		int digit = 0;
		int zipCodeSum = 0;
		int zipCodeCheckDigit = 0;
		for (int index = 0; index < kLengthOfZipCode; index++)
		{
			if (zipCodeString[index] == '1')
			{
				digit = 1;
			}
			else if (zipCodeString[index] == '2')
			{
				digit = 2;
			}
			else if (zipCodeString[index] == '3')
			{
				digit = 3;
			}
			else if (zipCodeString[index] == '4')
			{
				digit = 4;
			}
			else if (zipCodeString[index] == '5')
			{
				digit = 5;
			}
			else if (zipCodeString[index] == '6')
			{
				digit = 6;
			}
			else if (zipCodeString[index] == '7')
			{
				digit = 7;
			}
			else if (zipCodeString[index] == '8')
			{
				digit = 8;
			}
			else if (zipCodeString[index] == '9')
			{
				digit = 9;
			}
			else if (zipCodeString[index] == '0')
			{
				digit = 0;
			}

			zipCodeInteger = (zipCodeInteger * 10) + digit; //here is zip code in integer form
			zipCodeSum += digit;
			zipCodeCheckDigit = (((zipCodeSum / 10) + 1) * 10) - zipCodeSum;
		}
		return zipCodeCheckDigit;
	}

	/*
	Converts a number of integer data type to string data type

	@param number the integer number

	@return numberAsAString the number in string form
	*/
	string IntegerToStringConversion(int number)
	{
		string numberAsAString = " ";

		if (number = 1)
		{
			return numberAsAString = "1";
		}
		else if (number = 2)
		{
			return numberAsAString = "2";
		}
		else if (number = 3)
		{
			return numberAsAString = "3";
		}
		else if (number = 4)
		{
			return numberAsAString = "4";
		}
		else if (number = 5)
		{
			return numberAsAString = "5";
		}
		else if (number = 6)
		{
			return numberAsAString = "6";
		}
		else if (number = 7)
		{
			return numberAsAString = "7";
		}
		else if (number = 8)
		{
			return numberAsAString = "8";
		}
		else if (number = 9)
		{
			return numberAsAString = "9";
		}
		else if (number = 0)
		{
			return numberAsAString = "0";
		}
	}

	/*
	Detects if the input is a bar code or zip code and then converts it to it's opposing form

	@param validatedInput the bar code or string to be converted
	*/
	void Converter(string validatedInput)
	{
		if (validatedInput[0] == ':' || validatedInput[0] == '|')
		{
			cout << "Zip Code : " << BarCodeToZipCodeConverter(validatedInput) << endl;
		}
		else if (validatedInput[0] >= '0' && validatedInput[0] <= '9')
		{
			cout << "Bar Code : " << ZipCodeToBarCodeConverter(validatedInput) << endl;
		}
	}

	/*
	Prompts the user if they would like to rerun the program

	@return isAgain returns true if the user would like to rerun the program
	*/
	bool RunItAgain()
	{
		bool isAgain = 0;
		char answer = ' ';
		int counter = 0;
		cout << endl << "Care for another?" << endl
			 << "1. That was delightful. Yes, please." << endl
			 << "2. I've had all I can take" << endl;
		cin >> answer;
		bool isWrong = answer != '1' && answer != '2';
		while (isWrong)
		{
			counter++;
			if (counter == 5)
			{
				cout << endl << "You're really struggling with this aren't you?" << endl
					<< "Let me help, they're the two keys inbetween the ` and 3" << endl << endl;
			}
			if (counter == 10)
			{
				cout << endl << "No more for you!" << endl << endl;
				return isAgain = 0;
			}
			cout << "That's a dreadful answer. Please try again : ";
			cin.clear();
			cin.ignore(kEndOfLine, '\n');
			cin >> answer;
			isWrong = answer != '1' && answer != '2';
		}
		if (answer == '1')
		{
			cout << endl << "Splendid. Here you go." << endl;
			return isAgain = 1;
		}
		else if (answer == '2')
		{
			cout << endl << "Well I can't say I'm not dissappointed..." << endl << endl
				<< "Goodbye." << endl;
			return isAgain = 0;
		}

	}

	void TestCode()
	{
		//Check Digit
		int checkDigit = CheckDigit("95014");
		cout << "Check Digit: " << checkDigit << endl;
		checkDigit = CheckDigit("72762");
		cout << "Check Digit: " << checkDigit << endl;
		
		//ZipCodeToBarCodeConverter
		cout << ZipCodeToBarCodeConverter("72762") << endl; // ||:::|::|:||:::|:||::::|:|:::|||
		cout << ZipCodeToBarCodeConverter("12345") << endl; // |:::||::|:|::||::|::|:|:|::::|||

		//BarCodeToZipCodeConverter
		cout << BarCodeToZipCodeConverter("||:|:::|:|:||::::::||:|::|:::|||") << endl; //95014
		cout << BarCodeToZipCodeConverter("|:::||::|:|::||::|::|:|:|::::|||") << endl; //12345

		//BarCodeValidator
		bool isValidBarCode = 1;
		isValidBarCode = BarCodeValidator("||:|:::|:|:||::::::||:|::|:::|||");
		cout << isValidBarCode << endl;
		isValidBarCode = BarCodeValidator("||:|:::|:|:||::::::||:|::|:::||a");
		cout << isValidBarCode << endl;
		isValidBarCode = BarCodeValidator("||:|:::|:|:||::::::||:|::|:::||");
		cout << isValidBarCode << endl;
		
		//ZipCodeValidator
		bool isValidZipCode = 1;
		isValidZipCode = ZipCodeValidator("72762");
		cout << isValidZipCode << endl;
		isValidZipCode = ZipCodeValidator("7276a");
		cout << isValidZipCode << endl;
		return;
	}
};