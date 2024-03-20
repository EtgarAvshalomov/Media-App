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

private:

	vector<Media> watchlist;

public:

	User(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName, vector<Media> watchlist);
};

