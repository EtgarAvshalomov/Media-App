#pragma once
#include <iostream>
#include <vector>
#include "Media.h"
#include "Exceptions.h"
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

	User() = default;

	virtual void Menu() = 0; // A pure virtual method. To be inherited by the viewer and manager.

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

	void SetId();

	void SetFirstName();

	void SetLastName();

	void SetDayOfBirth();

	void SetMonthOfBirth();

	void setYearOfBirth();
};