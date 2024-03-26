#pragma once
#include "User.h"
#include "Series.h"
#include "Movie.h"
class Viewer :public User
{
private:

	vector<Movie> movieWatchlist;
	vector<Series> seriesWatchlist;

	void ClearMovieWatchlist();
	void ClearSeriesWatchlist();

public:

	Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void ViewerMenu();

	void AddMovieToWatchlist();

	void AddSeriesToWatchlist();

	void AddMovieToFile(Movie& toAdd);

	void AddSeriesToFile(Series& toAdd);

	void ReadMovieFromFile();

	void ReadSeriesFromFile();

	void WriteMovieToFile();

	void WriteSeriesToFile();

	void SearchMovieByName();

	void SearchSeriesByName();

	void SearchMediaByName();

	void DeleteSeriesFromWatchlist();

	void DeleteMovieFromWatchlist();

	void WatchMovie();

	void WatchSeries();

	bool CheckIfEmpty() {if (this->getID() == NULL) return true; else return false;}

	void PrintWatchlist();
};