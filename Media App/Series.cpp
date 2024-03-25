#include "Series.h"

Series::Series(string name, string category, int year, int seasons, int episodes):Media(name, category, year){
	this->seasons = seasons;
	this->episodes = episodes;
}

ostream& operator<<(ostream& out, const Series& m)
{
	out << m.getName() << " " << m.getCategory() << " " << m.getYear() << " " << m.getSeasons() << " " << m.getEpisodes()<< " " << m.getDateAdded() << endl;
	return out;
}