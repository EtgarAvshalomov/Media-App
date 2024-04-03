#include "Series.h"
#include <iostream>
#include <fstream>
#include <string>

static vector<Series> seriesDatabase;

Series::Series(string name, string category, int year, int seasons, int episodes):Media(name, category, year){
	this->seasons = seasons;
	this->episodes = episodes;
}

// Prints the objects data.
ostream& operator<<(ostream& out, const Series& m)
{
	out << m.getName() << " | Category: " << m.getCategory() << " | Year: " << m.getYear() << " | Seasons: " << m.getSeasons() << " | Episodes: " << m.getEpisodes();
	return out;
}

// Returns the series database vector.
vector<Series>& Series::GetSeriesDatabase()
{
	return seriesDatabase;
}

// Updates the series database vector from the Series Database.txt file.
void Series::ReadSeriesFromDatabase() throw(ifstream::failure)
{
	seriesDatabase.clear();

	string buffer;
	int numBuffer;
	Series series;
	string path = "Series Database.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) throw ifstream::failure("");
	else
	{
		while (!in.eof()) {

			getline(in, buffer);
			if (buffer == "") break;
			series.setName(buffer);

			getline(in, buffer);
			series.setCategory(buffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			series.setYear(numBuffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			series.setSeasons(numBuffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			series.setEpisodes(numBuffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			series.setDateAdded(numBuffer);

			seriesDatabase.emplace_back(series);

			getline(in, buffer);
		}

		in.close();
	}
}

bool Series::SeriesDatabaseIsEmpty()
{
	ReadSeriesFromDatabase();

	if (seriesDatabase.size() == 0) return true;

	return false;
}
