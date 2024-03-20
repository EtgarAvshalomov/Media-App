#pragma once
#include "User.h"
using namespace std;

class Manager :public User
{
public:

	Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);
	
};

