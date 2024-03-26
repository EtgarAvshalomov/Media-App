#include "Media.h"

Media::Media(string name, string category, int year) {
	this->name = name;
	this->category = category;
	this->year = year;
}

string Media::ChooseCategory()
{
	int choice;

	cout << endl;
	cout << "1. Sci-Fi" << endl;
	cout << "2. Horror" << endl;
	cout << "3. Comedy" << endl;
	cout << "4. Thriller" << endl;
	cout << endl;
	cin >> choice;

	switch (choice) {

	case 1:
		return "Sci-Fi";

	case 2:
		return "Horror";

	case 3:
		return "Comedy";

	case 4:
		return "Thriller";

	default:
		cout << "Unable to choose a category when adding a series to database.";
		break;
	}
}
