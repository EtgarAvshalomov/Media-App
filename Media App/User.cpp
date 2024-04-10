#define _CRT_SECURE_NO_WARNINGS
#include "User.h"
#include <string>
#include <ctime>


User::User(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName) {
	this->id = id;
	this->dayOfBirth = dayOfBirth;
	this->monthOfBirth = monthOfBirth;
	this->yearOfBirth = yearOfBirth;
	this->firstName = firstName;
	this->lastName = lastName;
}

// Sets the users id.
void User::SetId()
{
	bool loop = true;
	while (loop) {

		cout << "Please enter an id: ";

		string buffer;
		int num = 0;

		cin >> ws;
		getline(cin, buffer);

		try {

			Exceptions::CheckInt(100000000, 999999999, buffer);

			num = stoi(buffer);

			int check = num;
			int digitsNum = 0;

			while (check != 0) {
				check /= 10;
				digitsNum++;
			}

			if (digitsNum != 9) throw out_of_range("Digits");
		}
		catch (out_of_range e) {
			cerr << endl << "Please enter a 9 digit number" << endl << endl;
			continue;
		}
		catch (invalid_argument e) {
			if (string(e.what()) == "Space") {
				cerr << endl << "Spaces are not allowed" << endl << endl;
				continue;
			}
			cerr << endl << "Input must be a positive integer" << endl << endl;
			continue;
		}

		this->id = num;
		loop = false;
	}
}

// Sets the users first name.
void User::SetFirstName()
{
	bool loop = true;
	while (loop) {

		cout << endl << "Please enter your first name: ";

		string firstNameInput;

		cin >> ws;
		getline(cin, firstNameInput);

		try {
			Exceptions::CheckString(firstNameInput, 1, 24, true);
		}
		catch (out_of_range e) {
			cerr << endl << "Please enter between 1 and 24 characters" << endl;
			continue;
		}
		catch (invalid_argument e) {
			cerr << endl << "Only letters are allowed" << endl;
			continue;
		}

		this->firstName = firstNameInput;

		loop = false;
	}
}

// Sets users last name.
void User::SetLastName()
{
	bool loop = true;
	while (loop) {

		cout << endl << "Please enter your last name: ";

		string lastNameInput;

		cin >> ws;
		getline(cin, lastNameInput);

		try {
			Exceptions::CheckString(lastNameInput, 1, 24, true);
		}
		catch (out_of_range e) {
			cerr << endl << "Please enter between 1 and 24 characters" << endl;
			continue;
		}
		catch (invalid_argument e) {
			cerr << endl << "Only letters are allowed" << endl;
			continue;
		}

		this->lastName = lastNameInput;

		loop = false;
	}
}

// Sets the users day of birth.
void User::SetDayOfBirth() {
	
	bool loop = true;
	while (loop) {

		cout << endl << "Please enter your day of birth: ";

		string dayInput;

		int day = 0;

		cin >> ws;
		getline(cin, dayInput);

		try {

			Exceptions::CheckInt(1, 31, dayInput);

			day = stoi(dayInput);
		}
		catch (out_of_range e) {

			cerr << endl << "Please enter a number between 1 and 31" << endl;
			continue;
		}
		catch (invalid_argument e) {
			if (string(e.what()) == "Space") {
				cerr << endl << "Spaces are not allowed" << endl;
				continue;
			}
			cerr << endl << "Input must be a positive integer" << endl;
			continue;
		}

		this->dayOfBirth = day;
		loop = false;
	}
}

// Sets the users month of birth.
void User::SetMonthOfBirth()
{
	bool loop = true;
	while (loop) {

		cout << endl << "Please enter your month of birth: ";

		string monthInput;
		int month = 0;

		cin >> ws;
		getline(cin, monthInput);

		try {

			Exceptions::CheckInt(1, 12, monthInput);

			month = stoi(monthInput);
		}
		catch (out_of_range e) {

			cerr << endl << "Please enter a number between 1 and 12" << endl;
			continue;
		}
		catch (invalid_argument e) {
			if (string(e.what()) == "Space") {
				cerr << endl << "Spaces are not allowed" << endl;
				continue;
			}
			cerr << endl << "Input must be a positive integer" << endl;
			continue;
		}

		this->monthOfBirth = month;
		loop = false;
	}
}

// Sets the users year of birth.
void User::setYearOfBirth()
{
	bool loop = true;
	while (loop) {

		cout << endl << "Please enter your year of birth: ";

		string yearInput;

		int year = 0;

		time_t currentTime = time(nullptr);
		tm* localTime = localtime(&currentTime);
		int currentYear = localTime->tm_year + 1900;

		cin >> ws;
		getline(cin, yearInput);

		try {

			Exceptions::CheckInt(currentYear - 124, currentYear, yearInput);

			year = stoi(yearInput);
		}
		catch (out_of_range e) {

			cerr << endl << "Please enter a number between " << currentYear - 124 << " and " << currentYear << endl;
			continue;
		}
		catch (invalid_argument e) {
			if (string(e.what()) == "Space") {
				cerr << endl << "Spaces are not allowed" << endl;
				continue;
			}
			cerr << endl << "Input must be a positive integer" << endl;
			continue;
		}

		this->monthOfBirth = year;

		loop = false;
	}
}
