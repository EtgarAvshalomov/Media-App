#include "Series.h"
#include <iostream>
#include <fstream>
#include <string>

static vector<Series> seriesDatabase;

Series::Series(string name, string category, int year, int seasons, int episodes):Media(name, category, year){
	this->seasons = seasons;
	this->episodes = episodes;
}

ostream& operator<<(ostream& out, const Series& m)
{
	out << m.getName() << " " << m.getCategory() << " " << m.getYear() << " " << m.getSeasons() << " " << m.getEpisodes()<< " " << m.getDateAdded() << endl;
	return out;
}

vector<Series>& Series::GetSeriesDatabase()
{
	return seriesDatabase;
}

void Series::ReadSeriesFromDatabase()
{
	seriesDatabase.clear();

	string buffer;
	int numBuffer;
	Series series;
	string path = "Series Database.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "Series Database.txt open" << endl;

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
		cout << "Series Database.txt closed" << endl;
	}
}