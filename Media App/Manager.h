#pragma once
#include "User.h"

class Manager :public User
{
public:

	Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);
	
};

