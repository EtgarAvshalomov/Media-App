#include "User.h"

User::User(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName) {
	this->id = id;
	this->dayOfBirth = dayOfBirth;
	this->monthOfBirth = monthOfBirth;
	this->yearOfBirth = yearOfBirth;
	this->firstName = firstName;
	this->lastName = lastName;
}
