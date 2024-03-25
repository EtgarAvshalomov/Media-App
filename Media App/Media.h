#pragma once
#include<iostream>
using namespace std;

class Media
{
protected:

	string name;
	string category;
	int year;
	string dateAdded;
	
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

	string getDateAdded() const 
	{
		return dateAdded;
	}

	void setName(string name) {
		this->name = name;
	}

	void setCategory(string category) {
		this->category = category;
	}

	void setYear(int year)
	{
		this->year = year;
	}

	void setDateAdded(string date) {
		dateAdded = date;
		dateAdded.erase(remove(dateAdded.begin(), dateAdded.end(), '\n'), dateAdded.end());
	}
};

