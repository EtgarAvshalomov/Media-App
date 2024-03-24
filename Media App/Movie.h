#pragma once
#include "Media.h"

class Movie :public Media
{
private:

	int length;

	friend ostream& operator<<(ostream& out, const Movie& m);

public:

	Movie(string name, string category, int year, int length);
	
	Movie() = default;

	int getMovieLength() const
	{
		return length;
	}
};

