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
	string InvalidInput(string userInput);

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

	void TestCode();
}

#endif

