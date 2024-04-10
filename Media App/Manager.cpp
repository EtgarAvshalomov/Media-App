#define _CRT_SECURE_NO_WARNINGS
#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "Viewer.h"
#include "Exceptions.h"
#define RED "\033[91m"

using namespace std;

Manager::Manager(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName){

}

// Manager Menu
void Manager::Menu()
{
	cout << RED;

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
		cout << "5. View Database" << endl;
		cout << "0. Back To Main Menu" << endl << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 5);
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
			ManualAddSeriesToDatabase();
			break;

		case 2:
			ManualAddMovieToDatabase();
			break;

		case 3:
			DeleteMediaByName();
			break;

		case 4:
			DeleteMediaByCategory();
			break;

		case 5:
			PrintDatabase();
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

// Takes a Movie object and adds it to the database.
void Manager::AddMovieToDatabase(Movie& toAdd) throw(ofstream::failure)
{
	if (toAdd.getDateAdded() == NULL) { // Adds date of addition.
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

	ofstream out("Movies Database.txt", ios::app);
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
void Manager::AddSeriesToDatabase(Series& toAdd) throw(ofstream::failure)
{
	if (toAdd.getDateAdded() == NULL) { // Adds date of addition.
		time_t currentTime = time(nullptr);
		toAdd.setDateAdded(currentTime);
	}

	ofstream out("Series Database.txt", ios::app);
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

// Adds a movie to the database with user input.
void Manager::ManualAddMovieToDatabase()
{

	try {
		Movie::ReadMoviesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	vector<Movie> movieDatabase = Movie::GetMovieDatabase();

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

		bool nameFound = false;

		string tempInput = movie_name;

		transform(tempInput.begin(), tempInput.end(), tempInput.begin(), ::tolower); // Converts the input to lower case.

		for (int i = 0; i < movieDatabase.size(); i++) {

			string tempName = movieDatabase[i].getName();

			transform(tempName.begin(), tempName.end(), tempName.begin(), ::tolower); // Converts the input to lower case.

			if (tempInput == tempName) {
				cout << endl << "This series already exists in the database" << endl;
				nameFound = true;
			}
		}

		if (nameFound) continue;

		cout << endl << "Choose a Category: " << endl;

		movie_category = Media::ChooseCategory();
		if (movie_category == "Back") continue;

		bool year_loop = true;
		while (year_loop) {

			time_t currentTime = time(nullptr);
			tm* localTime = localtime(&currentTime);
			int currentYear = localTime->tm_year + 1900; // Gets the current year.

			cout << endl << "Enter The Year Of Release: " << endl << endl;

			cin >> ws;
			getline(cin, movie_year_input);

			try {
				Exceptions::CheckInt(1888, currentYear, movie_year_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between " << 1888 << " and " << currentYear << endl; // 1888 is the year when the first ever movie was made.
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be a positive integer" << endl;
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
				Exceptions::CheckInt(1, 600, movie_length_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 600" << endl; // The longest movie ever is 585 minutes long.
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be a positive integer" << endl;
				continue;
			}

			movie_length = stoi(movie_length_input);

			length_loop = false;
		}

		Movie new_movie(movie_name, movie_category, movie_year, movie_length); // Creates a movie with the input data.

		try {
			AddMovieToDatabase(new_movie);
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

		loop = false;

		cout << endl << "Successfully added a movie to the database!!" << endl;
	}
}

// Adds a series to the database with user input.
void Manager::ManualAddSeriesToDatabase()
{

	try {
		Series::ReadSeriesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	vector<Series> seriesDatabase = Series::GetSeriesDatabase();

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

		bool nameFound = false;

		string tempInput = series_name;

		transform(tempInput.begin(), tempInput.end(), tempInput.begin(), ::tolower); // Converts the input to lower case.

		for (int i = 0; i < seriesDatabase.size(); i++) {

			string tempName = seriesDatabase[i].getName();

			transform(tempName.begin(), tempName.end(), tempName.begin(), ::tolower); // Converts the input to lower case.

			if (tempInput == tempName) {
				cout << endl << "This series already exists in the database" << endl;
				nameFound = true;
			}
		}

		if (nameFound) continue;

		cout << endl << "Choose a Category: " << endl;

		series_category = Media::ChooseCategory();
		if (series_category == "Back") continue;

		bool year_loop = true;
		while (year_loop) {

			time_t currentTime = time(nullptr);
			tm* localTime = localtime(&currentTime);
			int currentYear = localTime->tm_year + 1900; // Gets the current year.

			cout << endl << "Enter The Year Of Release: ";

			cin >> ws;
			getline(cin, series_year_input);

			try {
				Exceptions::CheckInt(1888, currentYear, series_year_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please a number between " << 1888 << " and " << currentYear << endl; // 1888 is the year when the first ever movie was made.
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be a positive integer" << endl;
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
				Exceptions::CheckInt(1, 80, series_seasons_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 80" << endl; // The series with the most seasons has 76 seasons.
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be a positive integer" << endl;
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
				Exceptions::CheckInt(1, 240, series_episodes_input);
			}
			catch (out_of_range e) {

				cerr << endl << "Please enter a number between 1 and 240" << endl; // The series with the most series has 237 episodes per season.
				continue;
			}
			catch (invalid_argument e) {
				if (string(e.what()) == "Space") {
					cerr << endl << "Spaces are not allowed" << endl;
					continue;
				}
				cerr << endl << "Input must be a positive integer" << endl;
				continue;
			}

			series_episodes = stoi(series_episodes_input);

			episodes_loop = false;
		}

		Series new_series(series_name, series_category, series_year, series_seasons, series_episodes); // Creates a series with the input data.

		try {
			AddSeriesToDatabase(new_series);
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			return;
		}

		loop = false;

		cout << endl << "Successfully added a series to the database!!" << endl;
	}
}

// Deletes a movie from the database by category.
void Manager::DeleteMovieByCategory()
{
	bool loop = true;
	while (loop) {

		try {
			Movie::ReadMoviesFromDatabase();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

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

			for (int i = 0; unsigned(i) < movieDatabase.size(); i++) { // Prints the movies to the user.
				if (movieDatabase[i].getCategory() == category) {
					counter++;
					cout << counter << ". " << movieDatabase[i] << endl;
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

		for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) { // Deletes the chosen movie from the database vector.
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

		for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) { // Deletes the chosen movie from the watchlist vector.
			if (i->getName() == erasedMovie) {
				movieWatchlist.erase(i);
				break;
			}
		}

		cout << endl << "Movie was erased successfully!" << endl;

		try {
			ClearMovieDatabase();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < movieDatabase.size(); i++) { // Updates the movie database from the vector.

			try {
				AddMovieToDatabase(movieDatabase[i]);
			}
			catch (ifstream::failure) {
				cerr << endl << "Unable to open file!" << endl;
				break;
			}
		}

		try {
			Viewer::ClearMovieWatchlist();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) { // Updates the movie watchlist from the vector.

			try {
				Viewer::AddMovieToFile(movieWatchlist[i]);
			}
			catch (ifstream::failure) {
				cerr << endl << "Unable to open file!" << endl;
				break;
			}
		}
	}
}

// Deletes a series from the database by category.
void Manager::DeleteSeriesByCategory()
{
	bool loop = true;
	while (loop) {

		try {
			Series::ReadSeriesFromDatabase();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

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

			for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) { // Prints the series to the user.
				if (seriesDatabase[i].getCategory() == category) {
					counter++;
					cout << counter << ". " << seriesDatabase[i] << endl;
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

		for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) { // Deletes the chosen series from the database vector.
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

		for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) { // Delete the chosen series from watchlist vector.
			if (i->getName() == erasedSeries) {
				seriesWatchlist.erase(i);
				break;
			}
		}

		cout << endl << "Series was erased successfully!" << endl;

		try {
			ClearSeriesDatabase();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) { // Updates the series database from the vector.

			try {
				AddSeriesToDatabase(seriesDatabase[i]);
			}
			catch (ifstream::failure) {
				cerr << endl << "Unable to open file!" << endl;
				break;
			}
		}

		try {
			Viewer::ClearSeriesWatchlist();
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) { // Updates the series watchlist from the vector.

			try {
				Viewer::AddSeriesToFile(seriesWatchlist[i]);
			}
			catch (ifstream::failure) {
				cerr << endl << "Unable to open file!" << endl;
				break;
			}
		}
	}
}

// Menu for deletion by category.
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

// Deletes a movie from the database by name.
void Manager::DeleteMovieByName()
{
	try {
		Movie::ReadMoviesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	string buffer;
	string temp;
	bool movieFound = false;
	cout << endl << "Enter the name of the movie for deletion: ";

	cin >> ws;
	getline(cin, buffer);

	transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

	vector<Movie> movieDatabase = Movie::GetMovieDatabase();

	for (vector<Movie>::iterator i = movieDatabase.begin(); i != movieDatabase.end(); ++i) { // Itirates through the database vector to find the name of the movie.

		temp = i->getName();

		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

		if (temp == buffer) { // Checks if the names match.
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

				movieDatabase.erase(i); // Deletes the movie from the database vector.

				vector<Movie> movieWatchlist = Viewer::getMovieWatchlist();

				for (vector<Movie>::iterator i = movieWatchlist.begin(); i != movieWatchlist.end(); ++i) { // Deletes the movie from the movie watchlist.

					temp = i->getName();

					transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

					if (temp == buffer) {
						movieWatchlist.erase(i);
						break;
					}
				}

				try {
					Viewer::ClearMovieWatchlist();
				}
				catch (ifstream::failure) {
					cerr << endl << "Unable to open file!" << endl;
					break;
				}

				for (int i = 0; unsigned(i) < movieWatchlist.size(); i++) { // Updates the movie watchlist.

					try {
						Viewer::AddMovieToFile(movieWatchlist[i]);
					}
					catch (ifstream::failure) {
						cerr << endl << "Unable to open file!" << endl;
						break;
					}
				}

				break;
			}
			else if (choice == 2) return;
		}
	}

	if (!movieFound) {
		cout << endl << "No movie matches this name" << endl;
		return;
	}

	WriteMoviesToDatabase(movieDatabase);

	cout << endl << "Successfully deleted a movie from the database!" << endl;

}

// Deletes a series from the database by name.
void Manager::DeleteSeriesByName()
{

	try {
		Series::ReadSeriesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	string buffer;
	string temp;
	bool seriesFound = false;
	cout << endl << "Enter the name of the series for deletion: ";

	cin >> ws;
	getline(cin, buffer);

	transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

	vector<Series> seriesDatabase = Series::GetSeriesDatabase();

	for (vector<Series>::iterator i = seriesDatabase.begin(); i != seriesDatabase.end(); ++i) { // Itirates through the database vector to find the name of the series.

		temp = i->getName();

		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

		if (temp == buffer) {
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

				seriesDatabase.erase(i); // Deletes the series from the database vector.

				vector<Series> seriesWatchlist = Viewer::getSeriesWatchlist();

				for (vector<Series>::iterator i = seriesWatchlist.begin(); i != seriesWatchlist.end(); ++i) { // Deletes the series from the series watchlist.

					temp = i->getName();

					transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

					if (temp == buffer) {
						seriesWatchlist.erase(i);
						break;
					}
				}

				try {
					Viewer::ClearSeriesWatchlist();
				}
				catch (ifstream::failure) {
					cerr << endl << "Unable to open file!" << endl;
					break;
				}

				for (int i = 0; unsigned(i) < seriesWatchlist.size(); i++) { // Updates the series watchlist.
					
					try {
						Viewer::AddSeriesToFile(seriesWatchlist[i]);
					}
					catch (ifstream::failure) {
						cerr << endl << "Unable to open file!" << endl;
						return;
					}
				}

				break;
			}
			else if (choice == 2) return;
		}
	}

	if (!seriesFound) {
		cout << endl << "No series matches this name" << endl;
		return;
	}

	WriteSeriesToDatabase(seriesDatabase);

	cout << endl << "Successfully deleted a series from the database!" << endl;
}

// Menu for deletion by name.
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

// Opens the Movies Database.txt file in trunc mode to clear the file and closes it.
void Manager::ClearMovieDatabase() throw(ofstream::failure)
{
	ofstream out("Movies Database.txt", ios::trunc);
	if (!out.is_open()) throw ofstream::failure("");
	out.close();
} 

// Opens the Series Database.txt file in trunc mode to clear the file and closes it.
void Manager::ClearSeriesDatabase() throw(ofstream::failure)
{
	ofstream out("Series Database.txt", ios::trunc);
	if (!out.is_open()) throw ofstream::failure("");
	out.close();
}

// Updates the Movies Database.txt file by writing to it from the vector.
void Manager::WriteMoviesToDatabase(vector<Movie>& movieDatabase)
{
	try {
		ClearMovieDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	for (int i = 0; unsigned(i) < movieDatabase.size(); i++) {

		try {
			AddMovieToDatabase(movieDatabase[i]);
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}
	}
}

// Updates the Series Database.txt file by writing to it from the vector.
void Manager::WriteSeriesToDatabase(vector<Series>& seriesDatabase)
{
	try {
		ClearSeriesDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) {
		try {
			AddSeriesToDatabase(seriesDatabase[i]);
		}
		catch (ifstream::failure) {
			cerr << endl << "Unable to open file!" << endl;
			break;
		}
	}
}

// Database print menu. Prints the database the same way it is stored in the files.
void Manager::PrintDatabase()
{
	try {
		Series::ReadSeriesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}

	try {
		Movie::ReadMoviesFromDatabase();
	}
	catch (ifstream::failure) {
		cerr << endl << "Unable to open file!" << endl;
		return;
	}
	
	vector<Series> seriesDatabase = Series::GetSeriesDatabase();
	vector<Movie> movieDatabase = Movie::GetMovieDatabase();

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

		if (Series::SeriesDatabaseIsEmpty()) {
			cout << "The database is empty" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < seriesDatabase.size(); i++) { // Prints the series database.
			cout << seriesDatabase[i] << endl;
		}
		break;

	case 2: 

		if (Movie::MovieDatabaseIsEmpty()) {
			cout << "The database is empty" << endl;
			break;
		}

		for (int i = 0; unsigned(i) < movieDatabase.size(); i++) { // Prints the movies database.
			cout << movieDatabase[i] << endl;
		}
		break;

	default:
		break;
	}
}