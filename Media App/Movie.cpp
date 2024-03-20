#include "Movie.h"

Movie::Movie(string name, string category, int year, int movieLength):Media(name, category, year) {
	this->movieLength = movieLength;
}