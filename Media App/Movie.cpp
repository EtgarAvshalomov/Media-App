#include "Movie.h"

Movie::Movie(string name, string category, int year, int length):Media(name, category, year) {
	this->length = length;
}

ostream& operator<<(ostream& out, const Movie& m)
{
	out << m.getName() << " " << m.getCategory() << " " << m.getYear() << " " << m.getLength() << " " << m.getDateAdded() << endl;
	return out;
}