#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
#include <algorithm>
using namespace std;

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

void Viewer::ViewerMenu()
{
	int choice = 1;

	if (CheckIfEmpty() == true) // Place in ViewerMenu() later
	{
		SetId();
		SetFirstName();
		SetDayOfBirth();
	}

	cout << endl << "Welcome " + getFirstName() << "!" << endl << endl;
	cout << "1. Add Series To Watchlist" << endl;
	cout << "2. Add Movie To Watchlist" << endl;
	cout << "3. Search Media By Name" << endl;
	cout << "4. Watch Series From Watchlist" << endl;
	cout << "5. Watch Movie From Watchlist" << endl;
	cout << "6. Delete Series From Watchlist" << endl;
	cout << "7. Delete Movie From Watchlist" << endl;
	cout << "8. Back to Main Menu" << endl << endl;
	cout << "Choose an action: ";

	cin >> choice;
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
		cout << endl;
		break;

	default:
		cout << endl << "Error! Default switch in viewer menu!" << endl << endl;
		break;
	}
}

void Viewer::AddMovieToWatchlist()
{
	ReadMovieFromFile();

	Movie::ReadMoviesFromDatabase();

	vector<Movie> movieDatabase = Movie::GetMovieDatabase();

	sort(movieDatabase.begin(), movieDatabase.end(), greater<Movie>());

	string category = Media::ChooseCategory();

	int counter = 0;
	char c;

	for (int i = 0; i < movieDatabase.size(); i++) {
		if (movieDatabase[i].getCategory() == category) {
			counter++;
			cout << counter << ". " << movieDatabase[i].getName() << endl;
			cout << endl << "Do you wish do add this movie to your watchlist? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') {
				time_t currentTime = time(nullptr);
				movieDatabase[i].setDateAdded(currentTime);
				movieWatchlist.emplace_back(movieDatabase[i]);

				WriteMovieToFile();
				cout << "You have added " << movieDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == 'n' || c == 'N') continue;
		}
	}
}

void Viewer::AddSeriesToWatchlist()
{
	ReadSeriesFromFile();

	Series::ReadSeriesFromDatabase();

	vector<Series> seriesDatabase = Series::GetSeriesDatabase();

	sort(seriesDatabase.begin(), seriesDatabase.end(), greater<Series>());

	string category = Media::ChooseCategory();

	int counter = 0;
	char c;

	for (int i = 0; i < seriesDatabase.size(); i++) {
		if (seriesDatabase[i].getCategory() == category) {
			counter++;
			cout << counter << ". " << seriesDatabase[i].getName() << endl;
			cout << endl << "Do you wish do add this series to your watchlist? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') {
				time_t currentTime = time(nullptr);
				seriesDatabase[i].setDateAdded(currentTime);
				seriesWatchlist.emplace_back(seriesDatabase[i]);

				WriteSeriesToFile();
				cout << "You have added " << seriesDatabase[i].getName() << " to your watchlist!" << endl;
				return;
			}
			else if (c == 'n' || c == 'N') continue;
		}
	}
}

void Viewer::AddMovieToFile(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	toAdd.setDateAdded(currentTime);

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
	time_t currentTime = time(nullptr);
	toAdd.setDateAdded(currentTime);

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

	for (int i = 0; i < movieWatchlist.size(); i++) {
		AddMovieToFile(movieWatchlist[i]);
	}
}

void Viewer::WriteSeriesToFile(){

	ClearSeriesWatchlist();

	for (int i = 0; i < seriesWatchlist.size(); i++) {
		AddSeriesToFile(seriesWatchlist[i]);
	}
}

void Viewer::SearchMovieByName()
{
	Movie::ReadMoviesFromDatabase();
	vector <Movie> movieDatabase = Movie::GetMovieDatabase();

	string buffer;
	cout << endl << "Enter a movie name to search: " << endl;
	cin.get();
	getline(cin, buffer);

	char c;

	for (int i = 0; i < movieDatabase.size(); i++) {
		if (movieDatabase[i].getName() == buffer) {
			cout << movieDatabase[i].getName() << " Has been found!" << endl;
			cout << "Do you wish to add it to your watchlist? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') AddMovieToFile(movieDatabase[i]);

			cout << endl << "You have added " << movieDatabase[i].getName() << " to your watchlist!" << endl;
			return;
		}
	}

	cout << endl << "No movie matches this name" << endl;
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

	for (int i = 0; i < seriesDatabase.size(); i++) {
		if (seriesDatabase[i].getName() == buffer) {
			cout << seriesDatabase[i].getName() << " Has been found!" << endl;
			cout << "Do you wish to add it to your watchlist? Y/N" << endl << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') AddSeriesToFile(seriesDatabase[i]);

			cout << endl << "You have added " << seriesDatabase[i].getName() << " to your watchlist!" << endl;
			return;
		}
	}

	cout << endl << "No series matches this name" << endl;
}

void Viewer::SearchMediaByName()
{
	int choice = 0;

	cout << endl << "What would you like to search?" << endl;
	cout << "1. Movies" << endl;
	cout << "2. Series" << endl << endl;

	cin >> choice;

	switch (choice) {

	case 1:
		SearchMovieByName();
		break;

	case 2:
		SearchSeriesByName();
		break;

	default:
		cout << endl << "Invalid Value Entered While Searching For Media" << endl;
		break;
	}
}

void Viewer::DeleteSeriesFromWatchlist() {

	ReadSeriesFromFile();

	if (!movieWatchlist.size() == 0) {
		cout << endl << "Choose a series to delete" << endl;

		int choice = 0;

		for (int i = 0; i < seriesWatchlist.size(); i++) {
			cout << i + 1 << ". " << seriesWatchlist[i].getName() << endl;
		}

		cout << endl;
		cin >> choice;
		int counter = 0;

		for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) {
			counter++;
			if (counter == choice) {
				seriesWatchlist.erase(i);
				break;
			}
		}

		WriteSeriesToFile();
	}
	else if(movieWatchlist.size() == 0 && seriesWatchlist.size() == 0) cout << endl << "Your watchlist is empty" << endl << endl;
	else cout << endl << "There are no series in your watchlist" << endl << endl;
}

void Viewer::DeleteMovieFromWatchlist()
{
	ReadMovieFromFile();

	if (!movieWatchlist.size() == 0) {
		cout << endl << "Choose a movie to delete" << endl;

		int choice = 0;

		for (int i = 0; i < movieWatchlist.size(); i++) {
			cout << i + 1 << ". " << movieWatchlist[i].getName() << endl;
		}

		cout << endl;
		cin >> choice;
		int counter = 0;

		for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) {
			counter++;
			if (counter == choice) {
				movieWatchlist.erase(i);
				break;
			}
		}

		WriteMovieToFile();
	}
	else if (movieWatchlist.size() == 0 && seriesWatchlist.size() == 0) cout << endl << "Your watchlist is empty" << endl << endl;
	else cout << endl << "There are no movies in your watchlist" << endl << endl;
}

void Viewer::WatchMovie()
{
	ReadMovieFromFile();

	char c;

	for (int i = movieWatchlist.size(); i > 0; i--) {
		cout << endl << "Would you like to watch this movie? Y/N: " << endl;
		cout << movieWatchlist.size() - (i - 1) << ". " << movieWatchlist[i - 1].getName() << endl << endl;
		cin >> c;

		if (c == 'Y' || c == 'y') {
			cout << endl << "Watching: " << movieWatchlist[i - 1].getName() << "..." << endl << endl;
			cout << endl << "Press any key to continue...";
			cin.ignore();
			getchar();
		}
		else if (c == 'N' || c == 'n') {
			cout << endl << "Would you like to continue? Y/N" << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') continue;
			else if (c == 'N' || c == 'n') break;
		}
	}
}

void Viewer::WatchSeries()
{
	ReadSeriesFromFile();

	char c;

	for (int i = seriesWatchlist.size(); i > 0; i--) {
		cout << endl << "Would you like to watch this series? Y/N: " << endl;
		cout << seriesWatchlist.size() - (i - 1) << ". " << seriesWatchlist[i-1].getName() << endl << endl;
		cin >> c;

		if (c == 'Y' || c == 'y') {
			cout << endl << "Watching: " << seriesWatchlist[i-1].getName() << "..." << endl << endl;
			cout << endl << "Press any key to continue...";
			cin.ignore();
			getchar();
		}
		else if (c == 'N' || c == 'n') {
			cout << endl << "Would you like to continue? Y/N" << endl;
			cin >> c;

			if (c == 'Y' || c == 'y') continue;
			else if (c == 'N' || c == 'n') break;
		}
	}
}

void Viewer::PrintWatchlist()
{
	for (int i = 0; i < movieWatchlist.size(); i++) {
		cout << movieWatchlist[i];
	}

	for (int i = 0; i < seriesWatchlist.size(); i++) {
		cout << seriesWatchlist[i];
	}
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