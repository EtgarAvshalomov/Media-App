#pragma once
#include "User.h"
#include "Movie.h"

class Viewer :public User
{
private:

	vector<Media> watchlist;

public:
	Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName);

	void addMovieToWatchlist(Movie& toAdd);

	bool CheckIfEmpty() {if (this->getID() == NULL) return true; else return false;}


};