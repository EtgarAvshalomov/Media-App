#pragma once
#include "User.h"
#include "Movie.h"
#include "Series.h"
using namespace std;

class Manager :public User
{
private:

	void ClearMovieDatabase();
	void ClearSeriesDatabase();
	string ChooseCategory();

public:

	Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void ManagerMenu();

	void AddMovieToDatabase(Movie& toAdd);

	void AddSeriesToDatabase(Series& toAdd);

	void ManualAddMovieToDatabase();

	void ManualAddSeriesToDatabase();

	void DeleteMovieByCategory();

	void DeleteSeriesByCategory();

	void DeleteMediaByCategory();

	void DeleteMovieByName();

	void DeleteSeriesByName();

	void DeleteMediaByName();

	bool CheckIfEmpty() { if (this->getID() == NULL) return true; else return false; }

	void PrintDatabase();
};

