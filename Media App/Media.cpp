#include "Media.h"
#include <Windows.h>
#include <mmsystem.h>
#include "Viewer.h"
#include "Manager.h"
#include <string>
#include "Exceptions.h"
#define RESET "\033[0m"
#define RED "\033[91m"
#define CYAN "\033[96m"

#pragma comment(lib, "winmm.lib")
using namespace std;

Media::Media(string name, string category, int year) {
	this->name = name;
	this->category = category;
	this->year = year;
	this->dateAdded = NULL;
}

void Media::Program()
{
	PlaySound(TEXT("RiveR - Solo"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // Music

	Viewer viewer(0, 0, 0, 0, "", "");
	Manager manager(0, 0, 0, 0, "", "");

	int choice = 1;
	while (choice != NULL)
	{
		cout << RESET;
		cout << "Welcome to BambaFlix!" << endl << endl;
		cout << CYAN << "1. Viewer" << RESET << endl << RED << "2. Manager" << RESET << endl << "0. Exit" << endl << endl;

		try {
			choice = Exceptions::GetMenuInt(choice, 0, 2);
		}
		catch (out_of_range e) {
			cout << endl;
			continue;
		}
		catch (invalid_argument e) {
			cout << endl;
			continue;
		}

		switch (choice)
		{
		case 0:
			cout << endl <<  "Cya! ;D" << endl;
			exit(0);
			break;

		case 1:
			viewer.Menu();
			break;

		case 2:
			manager.Menu();
			break;

		default:
			break;
		}
	}
}

// Gets an input from the user and returns a string with the chosen category.
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
			cout << endl << "Unable to choose a category" << endl;
			break;
		}
	}
}