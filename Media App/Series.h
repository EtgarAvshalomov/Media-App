#pragma once
#include "Media.h"

class Series :public Media
{
	int seasons;
	int episodes;

	friend ostream& operator<<(ostream& out, const Series& m);

public:

	Series(string name, string category, int year, int seasons, int episodes);

	Series() = default;

	int getSeasons() const
	{
		return seasons;
	}

	int getEpisodes() const
	{
		return episodes;
	}

	void setSeasons(int seasons) {
		this->seasons = seasons;
	}

	void setEpisodes(int episodes) {
		this->episodes = episodes;
	}
};

