#pragma once
#include<iostream>
using namespace std;

class Media
{
protected:

	string name;
	string category;
	int year;
	int dateAdded;
	
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

	int getDateAdded() const 
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

	void setDateAdded(int dateAdded) {
		this->dateAdded = dateAdded;
	}

	static string ChooseCategory();

	bool operator > (const Media& str) const { // Checks which of the objects has the latest release date and addition date.
		if (getYear() != str.getYear())    return (getYear() > str.getYear());
		return (getDateAdded() > str.getDateAdded());
	}

	static void Program();
};

