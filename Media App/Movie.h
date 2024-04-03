#pragma once
#include "Media.h"
#include<vector>

class Movie :public Media
{
private:

	int length;

	friend ostream& operator<<(ostream& out, const Movie& m);

public:

	Movie(string name, string category, int year, int length);
	
	Movie() = default;

	int getLength() const
	{
		return length;
	}

	static vector<Movie>& GetMovieDatabase();

	void setLength(int length) {
		this->length = length;
	}

	static void ReadMoviesFromDatabase();

	static bool MovieDatabaseIsEmpty();
};