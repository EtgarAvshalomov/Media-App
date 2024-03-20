#include "Series.h"

Series::Series(string name, string category, int year, int seasons, int episodes):Media(name, category, year){
	this->seasons = seasons;
	this->episodes = episodes;
}