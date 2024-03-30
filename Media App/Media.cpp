#include "Media.h"
#include "Exceptions.h"

Media::Media(string name, string category, int year) {
	this->name = name;
	this->category = category;
	this->year = year;
	this->dateAdded = NULL;
}

string Media::ChooseCategory()
{
	bool loop = true;
	while (loop) {

		int choice = 0;

		cout << endl;
		cout << "1. Sci-Fi" << endl;
		cout << "2. Horror" << endl;
		cout << "3. Comedy" << endl;
		cout << "4. Thriller" << endl;
		cout << "0. Back" << endl;
		cout << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 4);
		}
		catch (out_of_range e) {
			continue;
		}
		catch (invalid_argument e) {
			continue;
		}

		switch (choice) {

		case 1:
			return "Sci-Fi";

		case 2:
			return "Horror";

		case 3:
			return "Comedy";

		case 4:
			return "Thriller";

		case 0:
			return "Back";

		default:
			cout << "Unable to choose a category when adding a series to database.";
			break;
		}
	}
}
