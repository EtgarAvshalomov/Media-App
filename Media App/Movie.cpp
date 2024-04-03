#include "Movie.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static vector<Movie> movieDatabase;

Movie::Movie(string name, string category, int year, int length):Media(name, category, year) {
	this->length = length;
}

// Prints the objects data.
ostream& operator<<(ostream& out, const Movie& m)
{
	out << m.getName() << " | Category: " << m.getCategory() << " | Year: " << m.getYear() << " | Length (Minutes): " << m.getLength();
	return out;
}

// Returns the movie database vector.
vector<Movie>& Movie::GetMovieDatabase() {
	return movieDatabase;
}

// Updates the movie database vector from the Movies Database.txt file.
void Movie::ReadMoviesFromDatabase() throw(ifstream::failure)
{

	movieDatabase.clear();

	string buffer;
	int numBuffer;
	Movie movie;
	string path = "Movies Database.txt";

	ifstream in(path, ios::in);
	if (!in.is_open()) throw ifstream::failure("");
	else
	{
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
			numBuffer = stoi(buffer);
			movie.setDateAdded(numBuffer);

			movieDatabase.emplace_back(movie);

			getline(in, buffer);
		}

		in.close();
	}
}