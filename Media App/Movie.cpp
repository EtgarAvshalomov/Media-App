#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

static vector<Movie> movieDatabase;

Movie::Movie(string name, string category, int year, int length):Media(name, category, year) {
	this->length = length;
}

ostream& operator<<(ostream& out, const Movie& m)
{
	out << m.getName() << " " << m.getCategory() << " " << m.getYear() << " " << m.getLength() << " " << m.getDateAdded() << endl;
	return out;
}

vector<Movie>& Movie::GetMovieDatabase() {
	return movieDatabase;
}

void Movie::ReadMoviesFromDatabase()
{

	movieDatabase.clear();

	string buffer;
	int numBuffer;
	Movie movie;
	string path = "Movies Database.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "Movies Database.txt open" << endl;

		while (!in.eof()) {

			getline(in, buffer);
			if (buffer == "") break;
			movie.setName(buffer);

			getline(in, buffer);
			movie.setCategory(buffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			movie.setYear(numBuffer);

			getline(in, buffer);
			numBuffer = stoi(buffer);
			movie.setLength(numBuffer);

			getline(in, buffer);
			movie.setDateAdded(buffer);

			movieDatabase.emplace_back(movie);

			getline(in, buffer);
		}

		in.close();
		cout << "Movies Database.txt closed" << endl;
	}
}