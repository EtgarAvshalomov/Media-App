#include "Viewer.h"
#include <vector>
#include <fstream>

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

void Viewer::addMovieToWatchlist(Movie& toAdd)
{
	watchlist.emplace_back(toAdd);

	ofstream out("Movie Watchlist.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later
	out << toAdd.getName() << " " << toAdd.getCategory() << " " << toAdd.getYear() << " " << toAdd.getDate() << " " << toAdd.getMovieLength() << "\n";
	out.close();
}
