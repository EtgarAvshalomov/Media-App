#pragma once
#include "User.h"
#include "Series.h"
#include "Movie.h"
class Viewer :public User
{
private:

	static void ReadMovieFromFile();

	static void ReadSeriesFromFile();

	void SearchMovieByName();

	void SearchSeriesByName();

	bool CheckViewerIfEmpty() { if (this->getID() == NULL) return true; else return false; } // Checks if the user had already signed in.

	void WriteMovieToFile();

	void WriteSeriesToFile();

	void AddMovieToWatchlist();

	void AddSeriesToWatchlist();

	void SearchMediaByName();

	void DeleteMovieFromWatchlist();

	void DeleteSeriesFromWatchlist();

	void WatchMovie();

	void WatchSeries();

	bool CheckIfMovieExists(string name);

	bool CheckIfSeriesExists(string name);

	bool MovieWatchlistIsEmpty();

	bool SeriesWatchlistIsEmpty();

	void PrintWatchlist();

public:

	Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void Menu() override;

	static vector<Movie> getMovieWatchlist();

	static vector<Series> getSeriesWatchlist();

	static void ClearMovieWatchlist();

	static void ClearSeriesWatchlist();

	static void AddMovieToFile(Movie& toAdd);

	static void AddSeriesToFile(Series& toAdd);
};