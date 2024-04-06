#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
#include "Exceptions.h"
#include <conio.h>
#define CYAN "\033[96m"

using namespace std;

static vector<Movie> movieWatchlist;
static vector<Series> seriesWatchlist;

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

// Viewer Menu
void Viewer::Menu()
{
	cout << CYAN;

	int choice = 1;
	bool loop = true;
	while (loop) {

		choice = 1;

		if (CheckViewerIfEmpty() == true)
		{
			cout << endl;
			SetId();
			SetFirstName();
			SetLastName();
			SetDayOfBirth();
			SetMonthOfBirth();
			setYearOfBirth();
		}

		cout << endl << "Hello " + getFirstName() << " " << getLastName() << "!" << endl << endl;
		cout << "1. Add Series To Watchlist" << endl;
		cout << "2. Add Movie To Watchlist" << endl;
		cout << "3. Search And Add Media By Name" << endl;
		cout << "4. Watch Series From Watchlist" << endl;
		cout << "5. Watch Movie From Watchlist" << endl;
		cout << "6. Delete Series From Watchlist" << endl;
		cout << "7. Delete Movie From Watchlist" << endl;
		cout << "8. View Watchlist" << endl;
		cout << "0. Back to Main Menu" << endl << endl;
		cout << "Choose an action: ";

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 8);
		}
		catch (out_of_range e) {
			continue;
		}
		catch (invalid_argument e) {
			continue;
		}

		switch (choice)
		{

		case 1:
			AddSeriesToWatchlist();
			break;

		case 2:
			AddMovieToWatchlist();
			break;

		case 3:
			SearchMediaByName();
			break;

		case 4:
			WatchSeries();
			break;

		case 5:
			WatchMovie();
			break;

		case 6:
			DeleteSeriesFromWatchlist();
			break;

		case 7:
			DeleteMovieFromWatchlist();
			break;

		case 8:
			PrintWatchlist();
			break;

		case 0:
			cout << endl;
			loop = false;
			break;

		default:
			cout << endl << "Error! Default switch in viewer menu!" << endl << endl;
			break;
		}
	}
}

// Returns the movie watchlist vector.
vector<Movie> Viewer::getMovieWatchlist()
{
	try {
		ReadMovieFromFile();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
	}
	return movieWatchlist;
}

// Returns the series watchlist vector.
vector<Series> Viewer::getSeriesWatchlist()
{
	try {
		ReadSeriesFromFile();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
	}
	return seriesWatchlist;
}

// Prints movies for the user to add to the watchlist. Adds the chosen movies to the watchlist.
void Viewer::AddMovieToWatchlist()
{
	bool loop = true;
	while (loop) {

		try {
			ReadMovieFromFile();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}

		try {
			Movie::ReadMoviesFromDatabase();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}

		vector<Movie> movieDatabase = Movie::GetMovieDatabase();

		if (movieDatabase.size() != 0) {

			sort(movieDatabase.begin(), movieDatabase.end(), greater<Movie>()); // Uses the comparison operator to sort the movies.

			string category = Media::ChooseCategory();

			if (category == "Back") {
				loop = false;
				break;
			}

			int counter = 1;
			int choice = 0;
			bool categoryFound = false;
			time_t currentTime;

			for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {
				if (movieDatabase[i].getCategory() == category) {

					categoryFound = true;

					if (CheckIfMovieExists(movieDatabase[i].getName())) { // Skips over movies that are already in the watchlist.
						continue;
					}

					bool inner_loop = true;
					while (inner_loop) {

						cout << endl << counter << ". " << movieDatabase[i] << endl;
						cout << endl << "Do you wish do add this movie to your watchlist?" << endl << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "0. Back" << endl << endl;

						try {
							choice = Exceptions::GetMenuInt(choice, 0, 2);
							inner_loop = false;
						}
						catch (out_of_range e) {
							continue;
						}
						catch (invalid_argument e) {
							continue;
						}

					}

					counter++;

					switch (choice) {

					case 1:

						currentTime = time(nullptr);
						movieDatabase[i].setDateAdded(currentTime); // Sets the date of addition to the database.

						movieWatchlist.emplace_back(movieDatabase[i]); // Adds the chosen movie to the movie database vector.

						WriteMovieToFile();

						cout << endl << "You have added " << movieDatabase[i].getName() << " to your watchlist!" << endl;

						break;

					case 2:
						continue;

					case 0:
						counter = 1;
						i = 0;
						category = Media::ChooseCategory();
						if (category == "Back") {
							loop = false;
							return;
						}
						continue;

					default:
						"Error! Default while adding a movie to watchlist";
						loop = false;
						break;
					}
				}
			}

			if (categoryFound == false) {
				cout << endl << "There are no movies from this category" << endl;
				continue;
			}

			cout << endl << "There are no more movies from this category" << endl;

		}
		else {
			cout << endl << "There are no movies in the database" << endl;
			loop = false;
		}
	}
}

void Viewer::AddSeriesToWatchlist()
{
	bool loop = true;
	while (loop) {

		try {
			ReadSeriesFromFile();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}

		try {
			Series::ReadSeriesFromDatabase();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}

		vector<Series> seriesDatabase = Series::GetSeriesDatabase();

		if (seriesDatabase.size() != 0) {

			sort(seriesDatabase.begin(), seriesDatabase.end(), greater<Series>()); // Uses the comparison operator to sort the series.

			string category = Media::ChooseCategory();

			if (category == "Back") {
				loop = false;
				break;
			}

			int counter = 1;
			int choice = 0;
			bool categoryFound = false;
			time_t currentTime;

			for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
				if (seriesDatabase[i].getCategory() == category) {

					categoryFound = true;

					if (CheckIfSeriesExists(seriesDatabase[i].getName())) {
						continue;
					}

					bool inner_loop = true;
					while (inner_loop) {

						cout << endl << counter << ". " << seriesDatabase[i] << endl;
						cout << endl << "Do you wish do add this series to your watchlist?" << endl << endl;
						cout << "1. Yes" << endl;
						cout << "2. No" << endl;
						cout << "0. Back" << endl << endl;

						try {
							choice = Exceptions::GetMenuInt(choice, 0, 2);
							inner_loop = false;
						}
						catch (out_of_range e) {
							continue;
						}
						catch (invalid_argument e) {
							continue;
						}
					}

					counter++;

					switch (choice) {

					case 1:

						currentTime = time(nullptr);
						seriesDatabase[i].setDateAdded(currentTime); // Sets the date of addition to the database.

						seriesWatchlist.emplace_back(seriesDatabase[i]); // Adds the chosen series to the series database vector.

						WriteSeriesToFile();

						cout << endl << "You have added " << seriesDatabase[i].getName() << " to your watchlist!" << endl;

						break;

					case 2:
						continue;

					case 0:
						counter = 1;
						i = 0;
						category = Media::ChooseCategory();
						if (category == "Back") {
							loop = false;
							return;
						}
						continue;

					default:
						"Error! Default while adding a series to watchlist";
						loop = false;
						break;
					}
				}
			}

			if (categoryFound == false) {
				cout << endl << "There are no series from this category" << endl;
				continue;
			}

			cout << endl << "There are no more series from this category" << endl;
		}
		else {
			cout << endl << "There are no series in the database" << endl;
			loop = false;
		}
	}
}

// Takes a Movie object and adds it to the watchlist.
void Viewer::AddMovieToFile(Movie& toAdd) throw(ofstream::failure)
{
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime); // Sets the date of addition to the watchlist.
	}

	ofstream out("Movies Watchlist.txt", ios::app);
	if (!out.is_open()) throw ofstream::failure("");
	out << toAdd.getName() << endl;
	out << toAdd.getCategory() << endl;
	out << toAdd.getYear() << endl;
	out << toAdd.getLength() << endl;
	out << toAdd.getDateAdded() << endl;
	out << endl;
	out.close();
}

// Takes a Series object and adds it to the database.
void Viewer::AddSeriesToFile(Series& toAdd) throw(ofstream::failure)
{
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime); // Sets the date of addition to the watchlist.
	}

	ofstream out("Series Watchlist.txt", ios::app);
	if (!out.is_open()) throw ofstream::failure("");
	out << toAdd.getName() << endl;
	out << toAdd.getCategory() << endl;
	out << toAdd.getYear() << endl;
	out << toAdd.getSeasons() << endl;
	out << toAdd.getEpisodes() << endl;
	out << toAdd.getDateAdded() << endl;
	out << endl;
	out.close();
}

// Updates the movie watchlist vector from the Movies Watchlist.txt file.
void Viewer::ReadMovieFromFile() throw(ifstream::failure)
{
	movieWatchlist.clear();

	Movie movie;
	string buffer;
	int numBuffer;
	string path = "Movies Watchlist.txt";
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

			movieWatchlist.emplace_back(movie);

			getline(in, buffer);
		}

		in.close();
	}
}

// Updates the series watchlist vector from the Series Watchlist.txt file.
void Viewer::ReadSeriesFromFile() throw(ifstream::failure)
{
	seriesWatchlist.clear();

	Series series;
	string buffer;
	int numBuffer;
	string path = "Series Watchlist.txt";
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

			seriesWatchlist.emplace_back(series);

			getline(in, buffer);
		}

		in.close();
	}
}

// Updates the Movies Watchlist.txt file from the movie watchlist vector.
void Viewer::WriteMovieToFile() {

	try {
		Viewer::ClearMovieWatchlist();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {

		try {
			Viewer::AddMovieToFile(movieWatchlist[i]);
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}
	}
}

// Updates the Series Watchlist.txt file from the series watchlist vector.
void Viewer::WriteSeriesToFile(){

	try {
		Viewer::ClearSeriesWatchlist();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {

		try {
			Viewer::AddSeriesToFile(seriesWatchlist[i]);
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}
	}
}

// Searches for a movie from the database by name. Adds the chosen movie to the watchlist.
void Viewer::SearchMovieByName()
{
	try {
		Movie::ReadMoviesFromDatabase();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	vector <Movie> movieDatabase = Movie::GetMovieDatabase();

	string buffer;
	string temp;
	cout << endl << "Enter a movie name to search: " << endl << endl;

	cin >> ws;
	getline(cin, buffer);

	transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

	string c;
	bool nameFound = false;

	for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {

		temp = movieDatabase[i].getName();

		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

		if (temp == buffer) { // Checks if the name matches a name in the database.

			nameFound = true;

			cout << endl << movieDatabase[i].getName() << " Has been found!" << endl;
			cout << endl << "Do you wish to add it to your watchlist? Y/N" << endl << endl;

			cin >> ws;
			getline(cin, c);

			try {
				Exceptions::CheckChar(c);
			}
			catch (invalid_argument) {
				cout << endl << "Invalid input" << endl;
				i--;
				continue;
			}

			if (c == "Y" || c == "y") {

				try {
					ReadMovieFromFile();
				}
				catch (ifstream::failure) {
					cout << endl << "Unable to open file!" << endl;
					break;
				}

				if (CheckIfMovieExists(movieDatabase[i].getName())) {
					cout << endl << movieDatabase[i].getName() << " Is already in your watchlist" << endl;
					break;
				}

				try {
					AddMovieToFile(movieDatabase[i]);
				}
				catch (ifstream::failure) {
					cout << endl << "Unable to open file!" << endl;
					break;
				}

				cout << endl << "You have added " << movieDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == "N" || c == "n") {
				break;
			}
		}
	}

	if (nameFound == false) {
		cout << endl << "No movie matches this name" << endl;
	}
}

// Searches for a series from the database by name. Adds the chosen series to the watchlist.
void Viewer::SearchSeriesByName()
{
	try {
		Series::ReadSeriesFromDatabase();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	vector <Series> seriesDatabase = Series::GetSeriesDatabase();

	string buffer;
	string temp;
	cout << endl << "Enter a series name to search: " << endl << endl;

	cin >> ws;
	getline(cin, buffer);

	transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

	string c;
	bool nameFound = false;

	for (int i = 0; i < seriesDatabase.size(); i++) {

		temp = seriesDatabase[i].getName();

		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

		if (temp == buffer) { // Checks if the name matches a name in the database.

			nameFound = true;

			cout << endl << seriesDatabase[i].getName() << " Has been found!" << endl;
			cout << endl << "Do you wish to add it to your watchlist? Y/N" << endl << endl;
			
			cin >> ws;
			getline(cin, c);

			try {
				Exceptions::CheckChar(c);
			}
			catch (invalid_argument) {
				cout << endl << "Invalid input" << endl;
				i--;
				continue;
			}

			if (c == "Y" || c == "y") {

				try {
					ReadSeriesFromFile();
				}
				catch (ifstream::failure) {
					cout << endl << "Unable to open file!" << endl;
					break;
				}

				if (CheckIfSeriesExists(seriesDatabase[i].getName())) {
					cout << endl << seriesDatabase[i].getName() << " Is already in your watchlist" << endl;
					break;
				}

				try {
					AddSeriesToFile(seriesDatabase[i]);
				}
				catch (ifstream::failure) {
					cout << endl << "Unable to open file!" << endl;
					break;
				}

				cout << endl << "You have added " << seriesDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == "N" || c == "n") {
				break;
			}
		}
	}

	if (nameFound == false) {
		cout << endl << "No series matches this name" << endl;
	}
}

// Search media by name menu.
void Viewer::SearchMediaByName()
{
	bool loop = true;
	while (loop) {

		int choice = 0;

		cout << endl << "What would you like to search?" << endl << endl;
		cout << "1. Series" << endl;
		cout << "2. Movies" << endl;
		cout << "0. Back" << endl << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 2);
		}
		catch (out_of_range e) {
			continue;
		}
		catch (invalid_argument e) {
			continue;
		}

		switch (choice) {

		case 1:
			SearchSeriesByName();
			break;

		case 2:
			SearchMovieByName();
			break;

		case 0:
			loop = false;
			break;

		default:
			cout << endl << "Invalid Value Entered While Searching For Media By Name" << endl;
			break;
		}
	}
}

// Deletes a series from the watchlist.
void Viewer::DeleteSeriesFromWatchlist() {

	bool loop = true;
	while (loop) {

		try {
			ReadSeriesFromFile();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}


		if (!seriesWatchlist.size() == 0) {

			cout << endl << "Choose a series to delete" << endl << endl;

			int choice = 0;
			int buffer = 0;

			for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) { // Prints the series from the watchlist.
				cout << i + 1 << ". " << seriesWatchlist[i] << endl;
				buffer = i + 1;
			}

			cout << "0. Back" << endl;

			cout << endl;
			
			try {
				choice = Exceptions::GetMenuInt(choice, 0, buffer);
			}
			catch (out_of_range e) {
				continue;
			}
			catch (invalid_argument e) {
				continue;
			}

			if (choice == 0) break;

			int counter = 0;
			for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) { // Itirates through the series watchlist vector and deletes the chosen series.
				counter++;
				if (counter == choice) {
					string buffer = i->getName();
					seriesWatchlist.erase(i);
					cout << endl << "You have succesfully deleted " << buffer << " from your watchlist!" << endl;
					break;
				}
			}

			WriteSeriesToFile();
		}
		else if (movieWatchlist.size() == 0 && seriesWatchlist.size() == 0) {
			cout << endl << "Your watchlist is empty" << endl;
			loop = false;
			break;
		}
		else {
			cout << endl << "There are no series in your watchlist" << endl;
			loop = false;
			break;
		}
	}
}

// Deletes a movie from the watchlist.
void Viewer::DeleteMovieFromWatchlist()
{
	bool loop = true;
	while (loop) {

		try {
			ReadMovieFromFile();
		}
		catch (ifstream::failure) {
			cout << endl << "Unable to open file!" << endl;
			break;
		}

		if (!movieWatchlist.size() == 0) {
			cout << endl << "Choose a movie to delete" << endl << endl;

			int choice = 0;
			int buffer = 0;

			for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) { // Prints the movies from the watchlist.
				cout << i + 1 << ". " << movieWatchlist[i] << endl;
				buffer = i + 1;
			}

			cout << "0. Back" << endl;

			cout << endl;
			
			try {
				choice = Exceptions::GetMenuInt(choice, 0, buffer);
			}
			catch (out_of_range e) {
				continue;
			}
			catch (invalid_argument e) {
				continue;
			}

			if (choice == 0) break;

			int counter = 0;
			for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) { // Itirates through the movies watchlist vector and deletes the chosen movie.
				counter++;
				if (counter == choice) {
					string buffer = i->getName();
					movieWatchlist.erase(i);
					cout << endl << "You have succesfully deleted " << buffer << " from your watchlist!" << endl;
					break;
				}
			}

			WriteMovieToFile();
		}
		else if (movieWatchlist.size() == 0 && seriesWatchlist.size() == 0) {
			cout << endl << "Your watchlist is empty" << endl;
			loop = false;
			break;
		}
		else {
			cout << endl << "There are no movies in your watchlist" << endl;
			loop = false;
			break;
		}
	}
}

// Allows the viewer to "watch" a movie.
void Viewer::WatchMovie()
{
	try {
		ReadMovieFromFile();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	if (movieWatchlist.size() == 0) {
		cout << endl << "There are no movies in your watchlist" << endl;
		return;
	}

	string c;

	for (int i = movieWatchlist.size(); i > 0; i--) { // Prints the movies from the watchlist (latest addition date is printed first).
		cout << endl << "Would you like to watch this movie? Y/N: " << endl;
		cout << endl << movieWatchlist.size() - (i - 1) << ". " << movieWatchlist[i - 1] << endl << endl;

		cin >> ws;
		getline(cin, c);

		try {
			Exceptions::CheckChar(c);
		}
		catch (invalid_argument) {
			cout << endl << "Invalid input" << endl;
			i++;
			continue;
		}

		if (c == "Y" || c == "y") {
			cout << endl << "Watching: " << movieWatchlist[i - 1].getName() << "..." << endl; // "Plays" the chosen movie to the viewer.
			cout << endl << "Press Enter to continue...";

			(void)_getch();
			cout << endl;

			if (i == 1) cout << endl << "There are no more movies in your watchlist" << endl;
		}
		else if (c == "N" || c == "n") {
			
			bool loop = true;
			while (loop) {

				cout << endl << "Would you like to continue? Y/N" << endl << endl;

				cin >> ws;
				getline(cin, c);

				try {
					Exceptions::CheckChar(c);
				}
				catch (invalid_argument) {
					cout << endl << "Invalid input" << endl;
					continue;
				}

				loop = false;
			}

			if (c == "Y" || c == "y") {
				if (i == 1) cout << endl << "There are no more movies in your watchlist" << endl;
				continue;
			}

			else if (c == "N" || c == "n") break;
		}
	}
}

// Allows the viewer to "watch" a series.
void Viewer::WatchSeries()
{

	try {
		ReadSeriesFromFile();
	}
	catch (ifstream::failure) {
		cout << endl << "Unable to open file!" << endl;
		return;
	}

	if (seriesWatchlist.size() == 0) {
		cout << endl << "There are no series in your watchlist" << endl;
		return;
	}

	string c;

	for (int i = seriesWatchlist.size(); i > 0; i--) { // Prints the series from the watchlist (latest addition date is printed first).

		cout << endl << "Would you like to watch this series? Y/N: " << endl << endl;
		cout << seriesWatchlist.size() - (i - 1) << ". " << seriesWatchlist[i-1] << endl << endl;
		
		cin >> ws;
		getline(cin, c);

		try {
			Exceptions::CheckChar(c);
		}
		catch (invalid_argument) {
			cout << endl << "Invalid input" << endl;
			i++;
			continue;
		}

		if (c == "Y" || c == "y") {

			cout << endl << "Watching: " << seriesWatchlist[i-1].getName() << "..." << endl; // "Plays" the chosen series to the viewer.
			cout << endl << "Press any key to continue...";

			(void)_getch();
			cout << endl;

			if (i == 1) cout << endl << "There are no more series in your watchlist" << endl;
		}
		else if (c == "N" || c == "n") {

			bool loop = true;
			while (loop) {

				cout << endl << "Would you like to continue? Y/N" << endl << endl;

				cin >> ws;
				getline(cin, c);

				try {
					Exceptions::CheckChar(c);
				}
				catch (invalid_argument) {
					cout << endl << "Invalid input" << endl;
					continue;
				}

				loop = false;
			}

			if (c == "Y" || c == "y") {
				if (i == 1) cout << endl << "There are no more series in your watchlist" << endl;
				continue;
			}

			else if (c == "N" || c == "n") break;
			
		}
	}
}

// Checks if a movie exists in the movie watchlist and returns a boolean.
bool Viewer::CheckIfMovieExists(string name)
{
	for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {
		if (movieWatchlist[i].getName() == name) {
			return true;
		}
	}
	return false;
}

// Checks if a series exists in the series watchlist and returns a boolean.
bool Viewer::CheckIfSeriesExists(string name)
{
	for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {
		if (seriesWatchlist[i].getName() == name) {
			return true;
		}
	}
	return false;
}

bool Viewer::MovieWatchlistIsEmpty()
{
	ReadMovieFromFile();

	if (movieWatchlist.size() == 0) return true;

	return false;
}

bool Viewer::SeriesWatchlistIsEmpty()
{
	ReadSeriesFromFile();

	if (seriesWatchlist.size() == 0) return true;

	return false;
}

// Opens the Series Watchlist.txt file in "trunc" mode and deletes all the data.
void Viewer::ClearSeriesWatchlist() throw(ofstream::failure)
{
	ofstream out("Series Watchlist.txt", ios::trunc);
	if (!out.is_open()) throw ofstream::failure("");
	out.close();
}

// Opens the Movies Watchlist.txt file in "trunc" mode and deletes all the data.
void Viewer::ClearMovieWatchlist() throw(ofstream::failure)
{
	ofstream out("Movies Watchlist.txt", ios::trunc);
	if (!out.is_open()) throw ofstream::failure("");
	out.close();
}

// Prints the watchlist. Sorted by the year of release, and then by addition date.
void Viewer::PrintWatchlist()
{

	int choice = 0;

	cout << endl;

	bool loop = true;
	while (loop) {

		cout << "1. Series" << endl;
		cout << "2. Movies" << endl;
		cout << "0. Back" << endl;
		cout << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 2);
		}
		catch (out_of_range e) {
			cout << endl;
			continue;
		}
		catch (invalid_argument e) {
			cout << endl;
			continue;
		}

		loop = false;
	}

	cout << endl;

	switch (choice) {
	case 1:

		if (SeriesWatchlistIsEmpty()) {
			cout << "The watchlist is empty" << endl;
			break;
		}

		try {
			ReadSeriesFromFile();
		}
		catch (ifstream::failure) {
			cerr << "Unable to open file!" << endl;
			break;
		}

		sort(seriesWatchlist.begin(), seriesWatchlist.end(), greater<Series>());

		for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) { // Prints the series watchlist.
			cout << seriesWatchlist[i] << endl;
		}
		break;

	case 2:

		if (MovieWatchlistIsEmpty()) {
			cout << "The watchlist is empty" << endl;
			break;
		}

		try {
			ReadMovieFromFile();
		}
		catch (ifstream::failure) {
			cerr << "Unable to open file!" << endl;
			break;
		}

		sort(movieWatchlist.begin(), movieWatchlist.end(), greater<Movie>());

		for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) { // Prints the movie watchlist.
			cout << movieWatchlist[i] << endl;
		}
		break;

	default:
		break;
	}
}