#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Movie.h"
#include "Viewer.h"
#include <ctime>
using namespace std;

int main() {
	Movie m("AOT", "Action", 2010, 120);
	Viewer v(211390869, 15, 5, 2000, "Etgar", "Avshalomov");
	Viewer b(208136911, 19, 5, 1999, "Ben", "Gofman");
	
	

	v.addMovieToWatchlist(m);

	return 0;
}