#include "Media.h"

Media::Media(string name, string category, int year) {
	this->name = name;
	this->category = category;
	this->year = year;
}

ostream& operator<<(ostream& out, const Media& m)
{
	out << m.getName() << " " << m.getCategory();
	return out;
}