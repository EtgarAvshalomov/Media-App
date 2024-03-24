#pragma once
#include <iostream>
#include <vector>
#include "Media.h"
using namespace std;

class User
{
protected:

	int id;
	int dayOfBirth;
	int monthOfBirth;
	int yearOfBirth;
	string firstName;
	string lastName;

public:
	User()=default;
	User(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	int getID() const
	{
		return id;
	}
	
	void SetId() 
	{
		cout << "Please enter an id: ";
		cin >> this->id;
	}
	void SetDayOfBirth()
	{
		cout << "Please enter Day, Month and year of birth: ";
		cin >> this->dayOfBirth;
		cin >> this->monthOfBirth;
		cin >> this->yearOfBirth;
	}

	void SetFirstName()
	{
		cout << "Please enter First and Last name: ";
		cin >> this->firstName;
		cin >> this->lastName;
	}

	int getDayOfBirth() const
	{
		return dayOfBirth;
	}

	int getMonthOfBirth() const
	{
		return monthOfBirth;
	}

	int getYearOfBirth() const
	{
		return yearOfBirth;
	}

	string getFirstName() const
	{
		return firstName;
	}

	string getLastName() const
	{
		return lastName;
	}
};