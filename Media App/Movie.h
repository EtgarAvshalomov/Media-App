#pragma once
#include "Media.h"

class Movie :public Media
{
	int movieLength;

	friend ostream& operator<<(ostream& out, const Movie& m);

public:

	Movie() = default;

	Movie(string name, string category, int year, int movieLength);

	int getMovieLength() const
	{
		return movieLength;
	}
};

