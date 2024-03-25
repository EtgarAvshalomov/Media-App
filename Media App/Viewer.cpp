#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include <ctime>
#include <string>
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
	default:
		cout << endl << "Error! Default switch in viewer menu!" << endl << endl;
		break;
	}
}

void Viewer::AddMovieToWatchlist(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);
	this->movieWatchlist.emplace_back(toAdd);
}

void Viewer::AddSeriesToWatchlist(Series& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);
	this->seriesWatchlist.emplace_back(toAdd);
}

void Viewer::AddMovieToFile(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);

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
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);

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
	Movie movie;
	string buffer;
	int numBuffer;
	string path = "Movies Watchlist.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "Movies Watchlist.txt open" << endl;

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

			movieWatchlist.emplace_back(movie);

			getline(in, buffer);
		}

		in.close();

		cout << "Movies Watchlist.txt closed" << endl;
	}
}

void Viewer::ReadSeriesFromFile()
{
	Series series;
	string buffer;
	int numBuffer;
	string path = "Series Watchlist.txt";
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "Series Watchlist.txt open" << endl;

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
			series.setDateAdded(buffer);

			seriesWatchlist.emplace_back(series);

			getline(in, buffer);
		}

		in.close();

		cout << "Movies Watchlist.txt closed" << endl;
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
