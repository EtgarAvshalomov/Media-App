#pragma once
#include<iostream>
using namespace std;

class Media
{
protected:

	string dateAdded;
	string name;
	string category;
	int year;
	
public:

	Media(string name, string category, int year);

	Media() = default;

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
		return dateAdded;
	}

	void setDateOfAdd(string date) {
		dateAdded = date;
		dateAdded.erase(remove(dateAdded.begin(), dateAdded.end(), '\n'), dateAdded.end());
	}
};

