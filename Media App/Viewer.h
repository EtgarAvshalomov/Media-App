#pragma once
#include "User.h"
#include "Series.h"
#include "Movie.h"
class Viewer :public User
{
private:

	vector<Movie> movieWatchlist;
	vector<Series> seriesWatchlist;

public:

	Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void ViewerMenu();

	void AddMovieToWatchlist(Movie& toAdd);

	void AddSeriesToWatchlist(Series& toAdd);

	void AddMovieToFile(Movie& toAdd);

	void AddSeriesToFile(Series& toAdd);

	void ReadMovieFromFile();

	void ReadSeriesFromFile();

	void SearchMovieByName();

	void SearchSeriesByName();

	void SearchMediaByName();

	bool CheckIfEmpty() {if (this->getID() == NULL) return true; else return false;}

	void PrintWatchlist();
};