#pragma once
#include<iostream>
using namespace std;

class Media
{
protected:

	string dateOfAdd;
	string name;
	string category;
	int year;
	
public:

	Media() = default;

	Media(string name, string category, int year);

	string getName() const
	{
		return name;
	}

	string getCategory() const
	{
		return category;
	}

	int getYear() const
	{
		return year;
	}

	string getDate() const 
	{
		return dateOfAdd;
	}

	void setDateOfAdd(string date) {
		dateOfAdd = date;
	}
};

