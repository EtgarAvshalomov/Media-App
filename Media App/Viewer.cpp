#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include "Movie.h"
#include <ctime>
using namespace std;

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

void Viewer::AddMovieToWatchlist(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateOfAdd(timeString);
	this->watchlist.emplace_back(toAdd);
}

void Viewer::AddSeriesToWatchlist(Series& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateOfAdd(timeString);
	this->watchlist.emplace_back(toAdd);
}

void Viewer::AddMovieToFile(Movie& toAdd)
{
	ofstream out("Watchlist.txt", ios::app);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.write((char*)&toAdd, sizeof(Movie));
	out.close();
}

void Viewer::ReadMovieFromFile()
{
	string path = "Watchlist.txt";
	ifstream fin;
	Movie currentMovie;
	fin.open(path, ios::in);
	if (!fin.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "File open, nice" << endl;
		while (fin.read((char*)&currentMovie, sizeof(Movie))) {
			this->watchlist.emplace_back(currentMovie);
		}
		for (int i = 0; i < 5; i++) {
			this->watchlist[i];
		}
	}
	fin.close();
}
