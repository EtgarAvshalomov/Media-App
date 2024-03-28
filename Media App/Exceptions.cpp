#include "Exceptions.h"
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

void Exceptions::CheckInt(int min, int max, string input) throw(out_of_range, invalid_argument)
{
	string buffer = input;
	int num = 0;
	num = stoi(buffer);

	float check = stof(buffer); // Check if decimal
	check = check / num;
	if (check > 1) throw invalid_argument("");

	if (num < min || num > max) throw out_of_range("");
}

int Exceptions::GetMenuInt(int choice, int min, int max) throw (out_of_range, invalid_argument)
{
	try {
		string buffer;
		cin >> buffer;

		Exceptions::CheckInt(min, max, buffer);

		choice = stoi(buffer);

		return choice;
	}
	catch (const out_of_range e) {
		cerr << endl << "Please enter a number between " << min << " and " << max << endl;
		throw out_of_range("");
	}
	catch (const invalid_argument& e) {
		cerr << endl << "Input must be an integer" << endl;
		throw invalid_argument("");
	}
	cout << endl;
}

void Exceptions::CheckString(string input, int min, int max) throw(out_of_range, invalid_argument)
{
	string buffer = input;

	if (buffer.length() < min || buffer.length() > max) throw out_of_range("");
}