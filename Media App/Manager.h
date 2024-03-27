#pragma once
#include "User.h"
#include "Movie.h"
#include "Series.h"
using namespace std;

class Manager :public User
{
private:

	void ManualAddMovieToDatabase();

	void ManualAddSeriesToDatabase();

	void DeleteMovieByCategory();

	void DeleteSeriesByCategory();

	void DeleteMovieByName();

	void DeleteSeriesByName();

	void ClearMovieDatabase();

	void ClearSeriesDatabase();

	void WriteMoviesToDatabase(vector<Movie>& movieDatabase);

	void WriteSeriesToDatabase(vector<Series>& seriesDatabase);

	bool CheckIfEmpty() { if (this->getID() == NULL) return true; else return false; }

	void PrintDatabase();

	void AddSeriesToDatabase(Series& toAdd);

	void AddMovieToDatabase(Movie& toAdd);

	void DeleteMediaByName();

	void DeleteMediaByCategory();

public:

	Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void ManagerMenu();
};