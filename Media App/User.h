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

	User(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	int getID() const
	{
		return id;
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