#include "Movie.h"

Movie::Movie(string name, string category, int year, int movieLength):Media(name, category, year) {
	this->movieLength = movieLength;
}

ostream& operator<<(ostream& out, const Movie& m)
{
	out <<"(" << m.getName() << ", " << m.getCategory() << ")";
	return out;
}