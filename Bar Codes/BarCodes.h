#ifndef BARCODES_H
#define BARCODES_H

#include <string>

using namespace std;

namespace barcodes
{
	/*
	Prompts user to enter the zip code or bar code and takes input
	
	@return Zip
	*/
	string UserInput();

	/*
	Checks to see if the user input is valid

	@param userInput the input from the user

	@return validInput
	*/
	string InputValidater(string userInput);

	/*
	Checks to see if the bar code is valid
	
	@param barCode the bar code to be tested
	@param &isValidBarCode is true if bar code is proper size and : or |
	*/
	bool BarCodeValidator(string barCode);

	/*
	Checks to see if the zip code is valid

	@param zipCode the zip code to be tested
	@param &isValidZipCode is true if the bar code is the proper size and only contains numbers
	*/
	bool ZipCodeValidator(string zipCode);

	/*
	Converts the user provided zip code into a bar code

	@param zipCode the zip code entered by the user

	@return barCode the bar code that represents the zip code
	*/
	string ZipCodeToBarCodeConverter(string zipCode);

	/*
	Converts the user provided bar code into a zip code

	@param barCode the bar code entered by the user

	@return zipCode the zip code that represents the bar code
	*/
	int BarCodeToZipCodeConverter(string zipCode);

	/*
	Converts string zip codes into integer zip codes and calculates check digit

	@param zipCodeString the zip code in string form

	@return zipCodeCheckDigit the check digit in integer form
	*/
	int CheckDigit(string zipCodeString);

	/*
	Converts a number of integer data type to string data type

	@param number the integer number

	@return numberAsAString the number in string form
	*/
	string IntegerToStringConversion(int number);

	/*
	Detects if the input is a bar code or zip code and then converts it to it's opposing form

	@param validatedInput the bar code or string to be converted
	*/
	void Converter(string validatedInput);

	/*
	Prompts the user if they would like to rerun the program

	@return isAgain returns true if the user would like to rerun the program
	*/
	bool RunItAgain();

	void TestCode();
}

#endif

