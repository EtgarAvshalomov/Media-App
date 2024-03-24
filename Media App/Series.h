#pragma once
#include "Media.h"

class Series :public Media
{
	int seasons;
	int episodes;

	friend ostream& operator<<(ostream& out, const Series& m);

public:

	Series(string name, string category, int year, int seasons, int episodes);

	int getSeasons() const
	{
		return seasons;
	}

	int getEpisodes() const
	{
		return episodes;
	}
};

