#include "Exceptions.h"
#include <string>
#include <typeinfo>

// Checks if the input has an operator
void Exceptions::OperatorCheck(const string& input)
{
	const string operators = "+-*/%^&|<>!=?:,.()_@#$\"'`~[]{}\\;";

	for (char c : input) {
		
		if (operators.find(c) != string::npos) {
			throw invalid_argument("Operator");
		}
	}
}

// Checks integer input
void Exceptions::CheckInt(int min, int max, string input) throw(out_of_range, invalid_argument)
{
	string buffer = input;
	int num = 0;
	num = stoi(buffer);

	float check = stof(buffer);
	check = check / num;	// Checks if decimal
	if (check > 1) throw invalid_argument("Decimal");

	for (char c : input) {

			if (c == ' ') throw invalid_argument("Space");

			if (isalpha(c)) throw invalid_argument("Letter");
	}

	OperatorCheck(buffer);

	if (num < min || num > max) throw out_of_range("");
}

// Checks the menu's input and returns it
int Exceptions::GetMenuInt(int choice, int min, int max) throw (out_of_range, invalid_argument)
{
	try {

		string buffer;
		
		cin >> ws;
		getline(cin, buffer);

		Exceptions::CheckInt(min, max, buffer);

		choice = stoi(buffer);

		return choice;
	}
	catch (const out_of_range e) {
		cerr << endl << "Please enter a number between " << min << " and " << max << endl;
		throw out_of_range("");
	}
	catch (const invalid_argument& e) {
		if (string(e.what()) == "Space") {
			cerr << endl << "Spaces are not allowed" << endl;
			throw invalid_argument("");
		}
		cerr << endl << "Input must be a positive integer" << endl;
		throw invalid_argument("");
	}

	cout << endl;
}

// Checks string input
void Exceptions::CheckString(string input,unsigned int min, unsigned int max, bool stringOnly) throw(out_of_range, invalid_argument)
{
	string buffer = input;

	if (buffer.length() < min || buffer.length() > max) throw out_of_range("");

	if (stringOnly) {
		for (char c : input) {
			if (!isalpha(c)) {
				if (c == ' ') {
					continue;
				}
				throw invalid_argument("");
			}
		}
	}
}

// Checks Y/N input
void Exceptions::CheckChar(string input) throw (invalid_argument)
{
	if (input != "Y" && input != "y" && input != "N" && input != "n") {
		throw invalid_argument("");
	}

	OperatorCheck(input);
}
