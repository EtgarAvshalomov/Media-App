#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctime>
using namespace std;

class Media
{
	time_t ben = time(NULL);
	string dataofadd = ctime(&ben);
	string name;
	string category;
	int year;
	
public:

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

	int getDate() const // Add a date later and then return it (Change the type).
	{
		return 0;
	}
};

