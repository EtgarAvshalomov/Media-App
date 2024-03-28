#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
#include "Exceptions.h"
using namespace std;

static vector<Movie> movieWatchlist;
static vector<Series> seriesWatchlist;

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

void Viewer::ViewerMenu()
{
	bool loop = true;
	while (loop) {

		int choice = 1;

		if (CheckViewerIfEmpty() == true)
		{
			cout << endl;
			SetId(); // Fix spaces with strings like "Some String"
			SetFirstName(); // Fix numbers
			SetLastName(); // Fix numbers
			SetDayOfBirth();
			SetMonthOfBirth();
			setYearOfBirth();
		}

		cout << endl << "Hello " + getFirstName() << " " << getLastName() << "!" << endl << endl;
		cout << "1. Add Series To Watchlist" << endl;
		cout << "2. Add Movie To Watchlist" << endl;
		cout << "3. Search Media By Name" << endl;
		cout << "4. Watch Series From Watchlist" << endl;
		cout << "5. Watch Movie From Watchlist" << endl;
		cout << "6. Delete Series From Watchlist" << endl;
		cout << "7. Delete Movie From Watchlist" << endl;
		cout << "0. Back to Main Menu" << endl << endl;
		cout << "Choose an action: ";

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 7);
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

vector<Movie> Viewer::getMovieWatchlist()
{
	ReadMovieFromFile();
	return movieWatchlist;
}

vector<Series> Viewer::getSeriesWatchlist()
{
	ReadSeriesFromFile();
	return seriesWatchlist;
}

void Viewer::AddMovieToWatchlist()
{
	bool loop = true;
	while (loop) {

		ReadMovieFromFile();

		Movie::ReadMoviesFromDatabase();

		vector<Movie> movieDatabase = Movie::GetMovieDatabase();

		if (movieDatabase.size() != 0) {

			sort(movieDatabase.begin(), movieDatabase.end(), greater<Movie>());

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

					if (CheckIfMovieExists(movieDatabase[i].getName())) {
						continue;
					}

					bool inner_loop = true;
					while (inner_loop) {

						cout << endl << counter << ". " << movieDatabase[i].getName() << endl;
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
						movieDatabase[i].setDateAdded(currentTime);
						movieWatchlist.emplace_back(movieDatabase[i]);

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

		ReadSeriesFromFile();

		Series::ReadSeriesFromDatabase();

		vector<Series> seriesDatabase = Series::GetSeriesDatabase();

		if (seriesDatabase.size() != 0) {

			sort(seriesDatabase.begin(), seriesDatabase.end(), greater<Series>());

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

						cout << endl << counter << ". " << seriesDatabase[i].getName() << endl;
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
						seriesDatabase[i].setDateAdded(currentTime);
						seriesWatchlist.emplace_back(seriesDatabase[i]);

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

void Viewer::AddMovieToFile(Movie& toAdd)
{
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

	ofstream out("Movies Watchlist.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out << toAdd.getName() << endl;
	out << toAdd.getCategory() << endl;
	out << toAdd.getYear() << endl;
	out << toAdd.getLength() << endl;
	out << toAdd.getDateAdded() << endl;
	out << endl;
	out.close();
}

void Viewer::AddSeriesToFile(Series& toAdd)
{
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

	ofstream out("Series Watchlist.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out << toAdd.getName() << endl;
	out << toAdd.getCategory() << endl;
	out << toAdd.getYear() << endl;
	out << toAdd.getSeasons() << endl;
	out << toAdd.getEpisodes() << endl;
	out << toAdd.getDateAdded() << endl;
	out << endl;
	out.close();
}

void Viewer::ReadMovieFromFile()
{
	movieWatchlist.clear();

	Movie movie;
	string buffer;
	int numBuffer;
	string path = "Movies Watchlist.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
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

void Viewer::ReadSeriesFromFile()
{
	seriesWatchlist.clear();

	Series series;
	string buffer;
	int numBuffer;
	string path = "Series Watchlist.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
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

void Viewer::WriteMovieToFile() {

	ClearMovieWatchlist();

	for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {
		AddMovieToFile(movieWatchlist[i]);
	}
}

void Viewer::WriteSeriesToFile(){

	ClearSeriesWatchlist();

	for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {
		AddSeriesToFile(seriesWatchlist[i]);
	}
}

void Viewer::SearchMovieByName()
{
	Movie::ReadMoviesFromDatabase();

	vector <Movie> movieDatabase = Movie::GetMovieDatabase();

	string buffer;
	cout << endl << "Enter a movie name to search: " << endl << endl;
	cin.get();
	getline(cin, buffer);

	char c;
	bool nameFound = false;

	for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {

		if (movieDatabase[i].getName() == buffer) {

			nameFound = true;

			cout << endl << movieDatabase[i].getName() << " Has been found!" << endl;
			cout << endl << "Do you wish to add it to your watchlist? Y/N" << endl << endl;

			cin >> c;

			if (c == 'Y' || c == 'y') {

				ReadMovieFromFile();

				if (CheckIfMovieExists(movieDatabase[i].getName())) {
					cout << endl << movieDatabase[i].getName() << " Is already in your watchlist!" << endl;
					break;
				}

				AddMovieToFile(movieDatabase[i]);
				cout << endl << "You have added " << movieDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == 'N' || c == 'n') {
				break;
			}
		}
	}

	if (nameFound == false) {
		cout << endl << "No movie matches this name" << endl;
	}
}

void Viewer::SearchSeriesByName()
{
	Series::ReadSeriesFromDatabase();

	vector <Series> seriesDatabase = Series::GetSeriesDatabase();

	string buffer;
	cout << endl << "Enter a series name to search: " << endl << endl;
	cin.get();
	getline(cin, buffer);

	char c;
	bool nameFound = false;

	for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {

		if (seriesDatabase[i].getName() == buffer) {

			nameFound = true;

			cout << endl << seriesDatabase[i].getName() << " Has been found!" << endl;
			cout << endl << "Do you wish to add it to your watchlist? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') {

				ReadSeriesFromFile();

				if (CheckIfSeriesExists(seriesDatabase[i].getName())) {
					cout << endl << seriesDatabase[i].getName() << " Is already in your watchlist!" << endl;
					break;
				}

				AddSeriesToFile(seriesDatabase[i]);
				cout << endl << "You have added " << seriesDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == 'N' || c == 'n') {
				break;
			}
		}
	}

	if (nameFound == false) {
		cout << endl << "No series matches this name" << endl;
	}
}

void Viewer::SearchMediaByName()
{
	bool loop = true;
	while (loop) {

		int choice = 0;

		cout << endl << "What would you like to search?" << endl << endl;
		cout << "1. Movies" << endl;
		cout << "2. Series" << endl;
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
			SearchMovieByName();
			break;

		case 2:
			SearchSeriesByName();
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

void Viewer::DeleteSeriesFromWatchlist() {

	bool loop = true;
	while (loop) {

		ReadSeriesFromFile();

		if (!seriesWatchlist.size() == 0) {
			cout << endl << "Choose a series to delete" << endl << endl;

			int choice = 0;
			int buffer = 0;

			for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {
				cout << i + 1 << ". " << seriesWatchlist[i].getName() << endl;
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
			for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) {
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

void Viewer::DeleteMovieFromWatchlist()
{
	bool loop = true;
	while (loop) {

		ReadMovieFromFile();

		if (!movieWatchlist.size() == 0) {
			cout << endl << "Choose a movie to delete" << endl << endl;

			int choice = 0;
			int buffer = 0;

			for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {
				cout << i + 1 << ". " << movieWatchlist[i].getName() << endl;
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
			for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) {
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

void Viewer::WatchMovie()
{
	ReadMovieFromFile();

	if (movieWatchlist.size() == 0) {
		cout << endl << "There are no movies in your watchlist" << endl;
		return;
	}

	char c;

	for (int i = movieWatchlist.size(); i > 0; i--) {
		cout << endl << "Would you like to watch this movie? Y/N: " << endl;
		cout << endl << movieWatchlist.size() - (i - 1) << ". " << movieWatchlist[i - 1].getName() << endl << endl;
		cin >> c;

		if (c == 'Y' || c == 'y') {
			cout << endl << "Watching: " << movieWatchlist[i - 1].getName() << "..." << endl;
			cout << endl << "Press Enter to continue...";
			cin.ignore();
			getchar();

			if (i == 1) cout << endl << "There are no more movies in your watchlist" << endl;
		}
		else if (c == 'N' || c == 'n') {
			cout << endl << "Would you like to continue? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') {
				if (i == 1) cout << endl << "There are no more movies in your watchlist" << endl;
				continue;
			}

			else if (c == 'N' || c == 'n') break;
		}
	}
}

void Viewer::WatchSeries()
{
	ReadSeriesFromFile();

	if (seriesWatchlist.size() == 0) {
		cout << endl << "There are no series in your watchlist" << endl;
		return;
	}

	char c;

	for (int i = seriesWatchlist.size(); i > 0; i--) {
		cout << endl << "Would you like to watch this series? Y/N: " << endl << endl;
		cout << seriesWatchlist.size() - (i - 1) << ". " << seriesWatchlist[i-1].getName() << endl << endl;
		cin >> c;

		if (c == 'Y' || c == 'y') {
			cout << endl << "Watching: " << seriesWatchlist[i-1].getName() << "..." << endl;
			cout << endl << "Press Enter to continue...";
			cin.ignore();
			getchar();

			if (i == 1) cout << endl << "There are no more series in your watchlist" << endl;
		}
		else if (c == 'N' || c == 'n') {
			cout << endl << "Would you like to continue? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') {
				if (i == 1) cout << endl << "There are no more series in your watchlist" << endl;
				continue;
			}

			else if (c == 'N' || c == 'n') break;
		}
	}
}

bool Viewer::CheckIfMovieExists(string name)
{
	for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {
		if (movieWatchlist[i].getName() == name) {
			return true;
		}
	}
	return false;
}

bool Viewer::CheckIfSeriesExists(string name)
{
	for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {
		if (seriesWatchlist[i].getName() == name) {
			return true;
		}
	}
	return false;
}

void Viewer::ClearSeriesWatchlist()
{
	ofstream out("Series Watchlist.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
}

void Viewer::ClearMovieWatchlist() 
{
	ofstream out("Movies Watchlist.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
}

void Viewer::PrintWatchlist()
{
	for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) {
		cout << movieWatchlist[i];
	}

	for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) {
		cout << seriesWatchlist[i];
	}
}