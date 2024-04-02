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

	bool CheckIfEmpty() { if (this->getID() == NULL) return true; else return false; } // Checks if the user had already signed in.

	void AddSeriesToDatabase(Series& toAdd);

	void AddMovieToDatabase(Movie& toAdd);

	void DeleteMediaByName();

	void DeleteMediaByCategory();

	void PrintDatabase();

public:

	Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void Menu() override;
};