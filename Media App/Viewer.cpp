#define _CRT_SECURE_NO_WARNINGS
#include "Viewer.h"
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

Viewer::Viewer(int id, int dayOfBirth, int monthOfBirth, int yearOfBirth, string firstName, string lastName):User(id, dayOfBirth, monthOfBirth, yearOfBirth, firstName, lastName) {

}

void Viewer::AddMovieToWatchlist(Movie& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateOfAdd(timeString);
	this->movieWatchlist.emplace_back(toAdd);
}

void Viewer::AddSeriesToWatchlist(Series& toAdd)
{
	time_t currentTime = time(nullptr);
	string timeString = ctime(&currentTime);
	toAdd.setDateOfAdd(timeString);
	this->seriesWatchlist.emplace_back(toAdd);
}

void Viewer::AddMovieToFile(Movie& toAdd)
{
	ofstream out("Watchlist.txt", ios::trunc);
	if (!out.is_open()) cout << "Unable to open file!"; // Throw an exception here later;
	out.write((char*)&toAdd, sizeof(Movie));
	out.close();
}

void Viewer::ReadMovieFromFile()
{
	string path = "Watchlist.txt";
	Movie movie;
	ifstream in(path, ios::in);
	if (!in.is_open()) { cout << "File cannot open!" << endl; }
	else
	{
		cout << "File open, nice" << endl;
		while (in.read((char*)&movie, sizeof(Movie))) {
			movieWatchlist.emplace_back(movie);
		}

		in.close();
		cout << "File closed, bombastic" << endl;
	}
}

void Viewer::PrintWatchlist()
{
	for (int i = 0; i < this->movieWatchlist.size(); i++) {
		cout << movieWatchlist[i];
	}
	for (int i = 0; i < this->seriesWatchlist.size(); i++) {
		cout << seriesWatchlist[i];
	}
}
