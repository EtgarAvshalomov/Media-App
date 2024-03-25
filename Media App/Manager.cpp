#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

Manager::Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName){

}

void Manager::AddMovieToDatabase(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);

	ofstream out("Movies Database.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out << toAdd.getName() << endl;
	out << toAdd.getCategory() << endl;
	out << toAdd.getYear() << endl;
	out << toAdd.getLength() << endl;
	out << toAdd.getDateAdded() << endl;
	out << endl;
	out.close();
}

void Manager::AddSeriesToDatabase(Series& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateAdded(timeString);

	ofstream out("Series Database.txt", ios::app);
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

void Manager::ManualAddMovieToDatabase()
{
	string movie_name;
	string movie_category;
	int movie_year;
	int movie_length;

	cout << "\n" << "Enter a Name For The Movie: ";
	cin.get();
	getline(cin, movie_name);
	cout << "Choose a Category: " << endl;
	movie_category = ChooseCategory();
	cout << "Enter The Year Of Release: ";
	cin >> movie_year;
	cout << "Enter The Length Of The Movie (In Minutes): ";
	cin >> movie_length;

	Movie new_movie(movie_name, movie_category, movie_year, movie_length);

	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	new_movie.setDateAdded(timeString);

	ofstream out("Movies Database.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out << new_movie.getName() << endl;
	out << new_movie.getCategory() << endl;
	out << new_movie.getYear() << endl;
	out << new_movie.getLength() << endl;
	out << new_movie.getDateAdded() << endl;
	out << endl;
	out.close();

	cout << "\n" << "Successfully added a movie to the database!!" << "\n" << "\n";
}

void Manager::ManualAddSeriesToDatabase()
{

	string series_name;
	string series_category;
	int series_year;
	int series_seasons;
	int series_episodes;

	cout << "\n" << "Enter a Name For The Series: ";
	cin.get();
	getline(cin, series_name);
	cout << endl << "Choose a Category: " << endl;
	series_category = ChooseCategory();
	cout << "Enter The Year Of Release: ";
	cin >> series_year;
	cout << "Enter The Number Of Seasons: ";
	cin >> series_seasons;
	cout << "Enter The Number Of Episodes (In Each Season): ";
	cin >> series_episodes;

	Series new_series(series_name, series_category, series_year, series_seasons, series_episodes);

	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	new_series.setDateAdded(timeString);

	ofstream out("Series Database.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out << new_series.getName() << endl;
	out << new_series.getCategory() << endl;
	out << new_series.getYear() << endl;
	out << new_series.getSeasons() << endl;
	out << new_series.getEpisodes() << endl;
	out << new_series.getDateAdded() << endl;
	out << endl;
	out.close();

	cout << "\n" << "Successfully added a series to the database!!" << "\n" << "\n";
}

void Manager::ReadMoviesFromDatabase()
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

void Manager::ReadSeriesFromDatabase()
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
			series.setDateAdded(buffer);

			seriesDatabase.emplace_back(series);

			getline(in, buffer);
		}

		in.close();
		cout << "Series Database.txt closed" << endl;
	}
}

void Manager::DeleteMovieByCategory()
{
	ReadMoviesFromDatabase();

	cout << "Choose a category: " << endl;

	string category = ChooseCategory();
	int choice = 0;
	int counter = 0;

	for (int i = 0; i < movieDatabase.size(); i++) {
		if (movieDatabase[i].getCategory() == category) {
			counter++;
			cout << counter << ". " << movieDatabase[i] << endl;
		}
	}

	if (counter == 0) {
		cout << endl << "There are no movies in that category in the watchlist." << endl;
		return;
	}

	cout << endl << "Choose a movie to delete: ";
	cin >> choice;

	counter = 0;
	for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) {
		if (i->getCategory() == category) {
			counter++;
			if (counter == choice) {
				movieDatabase.erase(i);
				break;
			}
		}
	}

	cout << endl << "Movie was erased successfully!" << endl;

	ClearMovieDatabase();

	for (int i = 0; i < movieDatabase.size(); i++) {
		AddMovieToDatabase(movieDatabase[i]);
	}
}

void Manager::DeleteSeriesByCategory()
{
	ReadSeriesFromDatabase();

	cout << "Choose a category: " << endl;

	string category = ChooseCategory();
	int choice = 0;
	int counter = 0;

	for (int i = 0; i < seriesDatabase.size(); i++) {
		if (seriesDatabase[i].getCategory() == category) {
			counter++;
			cout << counter << ". " << seriesDatabase[i] << endl;
		}
	}

	if (counter == 0) {
		cout << endl << "There are no series in that category in the watchlist." << endl;
		return;
	}

	cout << endl << "Choose a series to delete: ";
	cin >> choice;

	counter = 0;
	for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) {
		if (i->getCategory() == category) {
			counter++;
			if (counter == choice) {
				seriesDatabase.erase(i);
				break;
			}
		}
	}

	cout << endl << "Series was erased successfully!" << endl;

	ClearSeriesDatabase();

	for (int i = 0; i < seriesDatabase.size(); i++) {
		AddSeriesToDatabase(seriesDatabase[i]);
	}

}

void Manager::DeleteMediaByCategory() {

	int choice = 0;

	cout << "What would you like to delete?" << endl;
	cout << "1. Movie" << endl;
	cout << "2. Series" << endl << endl;
	cin >> choice;

	switch (choice) {

	case 1:
		DeleteMovieByCategory();
		break;

	case 2:
		DeleteSeriesByCategory();
		break;
		
	default:
		break;
	}
}

void Manager::DeleteMovieByName()
{
	ReadMoviesFromDatabase();

	string buffer;
	bool success = false;
	cout << "Enter the name of the movie for deletion: ";
	cin >> buffer;

	for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) {
		if (i->getName() == buffer) {
			movieDatabase.erase(i);
			success = true;
			break;
		}
	}

	if (!success) {
		cout << "Movie name not found in database" << endl;
		return;
	}

	ClearMovieDatabase();

	for (int i = 0; i < movieDatabase.size(); i++) {
		AddMovieToDatabase(movieDatabase[i]);
	}

	cout << "Successfully deleted a movie from the database!" << endl;

}

void Manager::DeleteSeriesByName()
{
	ReadSeriesFromDatabase();

	string buffer;
	bool success = false;
	cout << "Enter the name of the series for deletion: ";
	cin.get();
	getline(cin, buffer);

	for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) {
		if (i->getName() == buffer) {
			seriesDatabase.erase(i);
			success = true;
			break;
		}
	}

	if (!success) {
		cout << "Series name not found in database" << endl;
		return;
	}

	ClearSeriesDatabase();

	for (int i = 0; i < seriesDatabase.size(); i++) {
		AddSeriesToDatabase(seriesDatabase[i]);
	}

	cout << "Successfully deleted a series from the database!" << endl;
}

void Manager::DeleteMediaByName()
{
	int choice = 0;

	cout << "What would you like to delete?" << endl;
	cout << "1. Movie" << endl;
	cout << "2. Series" << endl << endl;
	cin >> choice;

	switch (choice) {

	case 1:
		DeleteMovieByName();
		break;

	case 2:
		DeleteSeriesByName();
		break;

	default:
		break;
	}
}

void Manager::PrintDatabase()
{
	ReadMoviesFromDatabase();
	ReadSeriesFromDatabase();

	for (int i = 0; i < movieDatabase.size(); i++) {
		cout << movieDatabase[i];
	}

	for (int i = 0; i < seriesDatabase.size(); i++) {
		cout << seriesDatabase[i];
	}
}

void Manager::ClearMovieDatabase()
{
	ofstream out("Movies Database.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
}

void Manager::ClearSeriesDatabase() {
	ofstream out("Series Database.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
}

string Manager::ChooseCategory()
{
	int choice;

	cout << endl;
	cout << "1. Sci-Fi" << endl;
	cout << "2. Horror" << endl;
	cout << "3. Comedy" << endl;
	cout << "4. Thriller" << endl;
	cout << endl;
	cin >> choice;

	switch (choice) {

	case 1:
		return "Sci-Fi";

	case 2:
		return "Horror";

	case 3:
		return "Comedy";

	case 4:
		return "Thriller";

	default:
		cout << "Unable to choose a category when adding a series to database.";
		break;
	}
}
