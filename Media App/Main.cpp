#include <iostream>
#include "Movie.h"
#include "Viewer.h"

int main() {

	Movie m("AOT", "Action", 2010, 120);

	Viewer v(211390869, 15, 5, 2000, "Etgar", "Avshalomov");

	v.addMovieToWatchlist(m);

	return 0;
}