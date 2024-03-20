#pragma once
#include "Media.h"

class Movie :public Media
{
	int movieLength;

public:

	Movie(string name, string category, int year, int movieLength);

	int getMovieLength() const
	{
		return movieLength;
	}
};

