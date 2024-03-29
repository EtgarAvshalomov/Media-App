#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "Viewer.h"
#include "Exceptions.h"

using namespace std;

Manager::Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName){

}

void Manager::ManagerMenu()
{
	bool loop = true;
	while (loop) {

		int choice = 1;

		if (CheckIfEmpty() == true)
		{
			cout << endl;
			SetId();
			SetFirstName();
			SetLastName();
			SetDayOfBirth();
			SetMonthOfBirth();
			setYearOfBirth();
		}

		cout << endl << "Hello " + getFirstName() << " " << getLastName() << "!" << endl; // Potentially add username and password for Manager.
		cout << endl << "1. Add Series To The Database" << endl;
		cout << "2. Add Movie To The Database" << endl;
		cout << "3. Delete Media By Name" << endl;
		cout << "4. Delete Media By Category" << endl;
		cout << "0. Back To Main Menu" << endl << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 4);
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
			ManualAddSeriesToDatabase(); // Check input
			break;

		case 2:
			ManualAddMovieToDatabase(); // Check input
			break;

		case 3:
			DeleteMediaByName(); // Check for lower case sensitivity later
			break;

		case 4:
			DeleteMediaByCategory();
			break;

		case 0:
			cout << endl;
			loop = false;
			break;

		default:
			cout << endl << "Error! Default switch in manager menu!" << endl << endl;
			break;
		}
	}
}

void Manager::AddMovieToDatabase(Movie& toAdd)
{
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

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
	if (toAdd.getDateAdded() == NULL) {
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

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
	bool loop = true;
	while (loop) {

		string movie_name;
		string movie_category;

		string movie_year_input;
		string movie_length_input;
		int movie_year = 0;
		int movie_length = 0;

		cout << endl << "Enter a Name For The Movie: ";

		cin >> ws;
		getline(cin, movie_name);

		cout << endl << "Choose a Category: " << endl;

		movie_category = Media::ChooseCategory();
		if (movie_category == "Back") continue;

		bool year_loop = true;
		while (year_loop) {

			time_t currentTime = time(nullptr);
			tm* localTime = localtime(&currentTime);
			int currentYear = localTime->tm_year + 1900;

			cout << endl << "Enter The Year Of Release: " << endl << endl;

			cin >> ws;
			getline(cin, movie_year_input);

			try {
				Exceptions::CheckInt(1888, currentYear, movie_year_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please a number between " << 1888 << " and " << currentYear << endl;
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be an integer" << endl;
				continue;
			}

			movie_year = stoi(movie_year_input);

			year_loop = false;
		}

		bool length_loop = true;
		while (length_loop) {

			cout << endl << "Enter The Length Of The Movie (In Minutes): ";

			cin >> ws;
			getline(cin, movie_length_input);

			try {
				Exceptions::CheckInt(1, 5400, movie_length_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 5400" << endl;
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be an integer" << endl;
				continue;
			}

			movie_length = stoi(movie_length_input);

			length_loop = false;
		}

		Movie new_movie(movie_name, movie_category, movie_year, movie_length);

		time_t currentTime = time(nullptr);
		new_movie.setDateAdded(currentTime);

		ofstream out("Movies Database.txt", ios::app);
		if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
		out << new_movie.getName() << endl;
		out << new_movie.getCategory() << endl;
		out << new_movie.getYear() << endl;
		out << new_movie.getLength() << endl;
		out << new_movie.getDateAdded() << endl;
		out << endl;
		out.close();

		loop = false;

		cout << endl << "Successfully added a movie to the database!!" << endl;
	}
}

void Manager::ManualAddSeriesToDatabase()
{

	string series_name;
	string series_category;

	string series_year_input;
	string series_seasons_input;
	string series_episodes_input;
	int series_year = 0;
	int series_seasons = 0;
	int series_episodes = 0;

	bool loop = true;
	while (loop) {

		cout << endl << "Enter a Name For The Series: ";

		cin >> ws;
		getline(cin, series_name);

		cout << endl << "Choose a Category: " << endl;

		series_category = Media::ChooseCategory();
		if (series_category == "Back") continue;

		bool year_loop = true;
		while (year_loop) {

			time_t currentTime = time(nullptr);
			tm* localTime = localtime(&currentTime);
			int currentYear = localTime->tm_year + 1900;

			cout << endl << "Enter The Year Of Release: ";

			cin >> ws;
			getline(cin, series_year_input);

			try {
				Exceptions::CheckInt(1888, currentYear, series_year_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please a number between " << 1888 << " and " << currentYear << endl;
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be an integer" << endl;
				continue;
			}

			series_year = stoi(series_year_input);

			year_loop = false;
		}

		bool seasons_loop = true;
		while (seasons_loop) {

			cout << endl << "Enter The Number Of Seasons: ";

			cin >> ws;
			getline(cin, series_seasons_input);

			try {
				Exceptions::CheckInt(1, 35, series_seasons_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 35" << endl;
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be an integer" << endl;
				continue;
			}

			series_seasons = stoi(series_seasons_input);

			seasons_loop = false;
		}

		bool episodes_loop = true;
		while (episodes_loop) {

			cout << endl << "Enter The Number Of Episodes (In Each Season): ";

			cin >> ws;
			getline(cin, series_episodes_input);

			try {
				Exceptions::CheckInt(1, 30, series_episodes_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 30" << endl;
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be an integer" << endl;
				continue;
			}

			series_episodes = stoi(series_episodes_input);

			episodes_loop = false;
		}

		Series new_series(series_name, series_category, series_year, series_seasons, series_episodes);

		time_t currentTime = time(nullptr);
		new_series.setDateAdded(currentTime);

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

		loop = false;

		cout << endl << "Successfully added a series to the database!!" << endl;
	}
}

void Manager::DeleteMovieByCategory()
{
	bool loop = true;
	while (loop) {

		Movie::ReadMoviesFromDatabase();

		cout << endl << "Choose a category: " << endl;

		string category = Media::ChooseCategory();

		if (category == "Back") {
			loop = false;
			break;
		}

		int choice = 0;
		int counter = 0;

		vector<Movie> movieDatabase = Movie::GetMovieDatabase();

		bool inner_loop = true;
		while (inner_loop) {

			counter = 0;

			cout << endl << "Choose a movie to delete: " << endl << endl;

			for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {
				if (movieDatabase[i].getCategory() == category) {
					counter++;
					cout << counter << ". " << movieDatabase[i].getName() << endl;
				}
			}

			if (counter == 0) {
				cout << "There are no movies in that category in the watchlist." << endl;
				inner_loop = false;
				break;
			}

			cout << "0. Back" << endl;

			cout << endl;

			try {
				choice = Exceptions::GetMenuInt(choice, 0, counter);
			}
			catch (out_of_range e) {
				continue;
			}
			catch (invalid_argument e) {
				continue;
			}

			inner_loop = false;
		}

		if (choice == 0) continue;

		string erasedMovie;
		counter = 0;

		for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) { // Delete movie from database
			if (i->getCategory() == category) {
				counter++;
				if (counter == choice) {
					erasedMovie = i->getName();
					movieDatabase.erase(i);
					break;
				}
			}
		}

		vector<Movie> movieWatchlist = Viewer::getMovieWatchlist();

		for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) { // Delete movie from watchlist
			if (i->getName() == erasedMovie) {
				movieWatchlist.erase(i);
				break;
			}
		}

		cout << endl << "Movie was erased successfully!" << endl;

		ClearMovieDatabase();

		for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {
			AddMovieToDatabase(movieDatabase[i]);
		}

		Viewer::ClearMovieWatchlist();

		for (int i = 0; i < movieWatchlist.size(); i++) {
			Viewer::AddMovieToFile(movieWatchlist[i]);
		}
	}
}

void Manager::DeleteSeriesByCategory()
{
	bool loop = true;
	while (loop) {

		Series::ReadSeriesFromDatabase();

		cout << endl << "Choose a category: " << endl;

		string category = Media::ChooseCategory();

		if (category == "Back") {
			loop = false;
			break;
		}

		int choice = 0;
		int counter = 0;

		vector<Series> seriesDatabase = Series::GetSeriesDatabase();

		bool inner_loop = true;
		while (inner_loop) {

			counter = 0;

			cout << endl << "Choose a series to delete: " << endl << endl;

			for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
				if (seriesDatabase[i].getCategory() == category) {
					counter++;
					cout << counter << ". " << seriesDatabase[i].getName() << endl;
				}
			}

			if (counter == 0) {
				cout << "There are no series in that category in the watchlist." << endl;
				inner_loop = false;
				break;
			}

			cout << "0. Back" << endl;

			cout << endl;

			try {
				choice = Exceptions::GetMenuInt(choice, 0, counter);
			}
			catch (out_of_range e) {
				continue;
			}
			catch (invalid_argument e) {
				continue;
			}

			inner_loop = false;
		}

		if (choice == 0) continue;

		string erasedSeries;
		counter = 0;
		for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) {
			if (i->getCategory() == category) {
				counter++;
				if (counter == choice) {
					erasedSeries = i->getName();
					seriesDatabase.erase(i);
					break;
				}
			}
		}

		vector<Series> seriesWatchlist = Viewer::getSeriesWatchlist();

		for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) { // Delete movie from watchlist
			if (i->getName() == erasedSeries) {
				seriesWatchlist.erase(i);
				break;
			}
		}

		cout << endl << "Series was erased successfully!" << endl;

		ClearSeriesDatabase();

		for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
			AddSeriesToDatabase(seriesDatabase[i]);
		}

		Viewer::ClearSeriesWatchlist();

		for (int i = 0; i < seriesWatchlist.size(); i++) {
			Viewer::AddSeriesToFile(seriesWatchlist[i]);
		}
	}
}

void Manager::DeleteMediaByCategory() {

	bool loop = true;
	while (loop) {

		int choice = 0;

		cout << endl << "What would you like to delete?" << endl << endl;
		cout << "1. Series" << endl;
		cout << "2. Movie" << endl;
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

			DeleteSeriesByCategory();
			break;

		case 2:

			DeleteMovieByCategory();
			break;

		case 0:
			loop = false;
			break;

		default:
			cout << endl << "Default switch while deleting media by category" << endl;
			break;
		}
	}
}

void Manager::DeleteMovieByName()
{
	Movie::ReadMoviesFromDatabase();

	string buffer;
	bool movieFound = false;
	cout << endl << "Enter the name of the movie for deletion: ";
	cin.get();
	getline(cin, buffer);
	vector<Movie> movieDatabase = Movie::GetMovieDatabase();

	for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) {
		if (i->getName() == buffer) {
			movieFound = true;

			int choice = 0;

			bool loop = true;
			while (loop) {

				cout << endl << i->getName() << " Was found! Would you like to delete it from the database?" << endl << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl << endl;

				try {
					choice = Exceptions::GetMenuInt(choice, 1, 2);
				}
				catch (out_of_range e) {
					continue;
				}
				catch (invalid_argument e) {
					continue;
				}

				loop = false;
			}

			if (choice == 1) {
				movieDatabase.erase(i);

				vector<Movie> movieWatchlist = Viewer::getMovieWatchlist();

				for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) {
					if (i->getName() == buffer) {
						movieWatchlist.erase(i);
						break;
					}
				}

				Viewer::ClearMovieWatchlist();

				for (int i = 0; i < movieWatchlist.size(); i++) {
					Viewer::AddMovieToFile(movieWatchlist[i]);
				}

				break;
			}
			else if (choice == 2) return;
		}
	}

	if (!movieFound) {
		cout << endl << "Movie was not found in database" << endl;
		return;
	}

	WriteMoviesToDatabase(movieDatabase);

	cout << endl << "Successfully deleted a movie from the database!" << endl;

}

void Manager::DeleteSeriesByName()
{
	Series::ReadSeriesFromDatabase();

	string buffer;
	bool seriesFound = false;
	cout << endl << "Enter the name of the series for deletion: ";
	cin.get();
	getline(cin, buffer);
	vector<Series> seriesDatabase = Series::GetSeriesDatabase();

	for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) {
		if (i->getName() == buffer) {
			seriesFound = true;

			int choice = 0;

			bool loop = true;
			while (loop) {

				cout << endl << i->getName() << " Was found! Would you like to delete it from the database?" << endl << endl;
				cout << "1. Yes" << endl;
				cout << "2. No" << endl << endl;

				try {
					choice = Exceptions::GetMenuInt(choice, 1, 2);
				}
				catch (out_of_range e) {
					continue;
				}
				catch (invalid_argument e) {
					continue;
				}

				loop = false;
			}

			if (choice == 1) {
				seriesDatabase.erase(i);

				vector<Series> seriesWatchlist = Viewer::getSeriesWatchlist();

				for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) {
					if (i->getName() == buffer) {
						seriesWatchlist.erase(i);
						break;
					}
				}

				Viewer::ClearSeriesWatchlist();

				for (int i = 0; i < seriesWatchlist.size(); i++) {
					Viewer::AddSeriesToFile(seriesWatchlist[i]);
				}

				break;
			}
			else if (choice == 2) return;
		}
	}

	if (!seriesFound) {
		cout << endl << "Series was not found in database" << endl;
		return;
	}

	WriteSeriesToDatabase(seriesDatabase);

	cout << endl << "Successfully deleted a series from the database!" << endl;
}

void Manager::DeleteMediaByName()
{
	bool loop = true;
	while (loop) {

		int choice = 0;

		cout << endl << "What would you like to delete?" << endl << endl;
		cout << "1. Series" << endl;
		cout << "2. Movie" << endl;
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
			DeleteSeriesByName();
			break;

		case 2:
			DeleteMovieByName();
			break;

		case 0:
			loop = false;
			break;

		default:
			break;
		}
	}
}

void Manager::PrintDatabase()
{
	Movie::ReadMoviesFromDatabase();
	Series::ReadSeriesFromDatabase();

	vector<Movie> movieDatabase = Movie::GetMovieDatabase();
	vector<Series> seriesDatabase = Series::GetSeriesDatabase();

	for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {
		cout << movieDatabase[i];
	}

	for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
		cout << seriesDatabase[i];
	}
}

void Manager::ClearMovieDatabase() // Move later to Movie
{
	ofstream out("Movies Database.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
} 

void Manager::ClearSeriesDatabase() //Move later to series
{
	ofstream out("Series Database.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.close();
}

void Manager::WriteMoviesToDatabase(vector<Movie>& movieDatabase)
{
	ClearMovieDatabase();

	for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {
		AddMovieToDatabase(movieDatabase[i]);
	}
}

void Manager::WriteSeriesToDatabase(vector<Series>& seriesDatabase)
{
	ClearSeriesDatabase();

	for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
		AddSeriesToDatabase(seriesDatabase[i]);
	}
}
