#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include "Movie.h"
#include "Viewer.h"
#include "Manager.h"
#include "User.h"
#include <ctime>
#include <fstream>
using namespace std;

int main()
{
	Viewer viewer(0, 0, 0, 0, "", "");
	Manager manager(0, 0, 0, 0, "", "");

	//Movie m1("Cychka", "Pizda", 6969, 8);
	//Series s2("My Little Pony", "Horror", 2013, 4, 12);
	//Series s3("Breaking Bad", "Comedy", 1995, 5, 62);

	//viewer.AddSeriesToFile(s2);
	//viewer.ReadSeriesFromFile();
	//viewer.PrintWatchlist();

	int choice = 1;
	while (choice!=NULL)
	{
		cout << "Welcome to BambaFlix!" << endl << endl;
		cout << "1. Viewer" << endl << "2. Manager" << endl << "0. Exit" << endl << endl;
		cin >> choice; // Throw exceptions later
		cout << endl;
		switch (choice)
		{
		case 0:
			cout << "Cya! ;D" << endl;
			exit(0);
			break;

		case 1:

			if (viewer.CheckIfEmpty() == true) // Place in ViewerMenu() later
			{
				viewer.SetId();
				viewer.SetFirstName();
				viewer.SetDayOfBirth();
			}

			cout << endl << "Welcome " + viewer.getFirstName() << "!" << endl << endl;
			cout << "1. Add Series To Watchlist" << endl;
			cout << "2. Add Movie To Watchlist" << endl;
			cout << "3. Search Media By Name" << endl;
			cout << "4. Watch Series From Watchlist" << endl;
			cout << "5. Watch Movie From Watchlist" << endl;
			cout << "6. Delete Series From Watchlist" << endl;
			cout << "7. Delete Movie From Watchlist" << endl;
			cout << "8. Back to Main Menu" << endl << endl;
			cout << "Choose an action: ";

			cin >> choice;
			switch (choice)
			{
			default:
				cout << endl << "Error! Default switch in viewer menu!" << endl << endl;
				break;
			}

			break;

		case 2:

			if (manager.CheckIfEmpty() == true)
			{
				manager.SetId();
				manager.SetFirstName();
				manager.SetDayOfBirth();
			}

			cout << endl << "Welcome " + manager.getFirstName() << "!" << endl << endl;
			cout << "1. Add Series To The Database" << endl;
			cout << "2. Add Movie To The Database" << endl;
			cout << "3. Delete Media By Name" << endl;
			cout << "4. Delete Media By Category" << endl;
			cout << "5. Back To Main Menu" << endl << endl;

			cin >> choice;
			switch (choice)
			{

			case 1:
				manager.ManualAddSeriesToDatabase();
				break;

			case 2:
				manager.ManualAddMovieToDatabase();
				break;

			case 3:
				manager.DeleteMediaByName(); // Check for lower case sensitivity later
				break;

			case 4:
				manager.DeleteMediaByCategory();
				break;
				
			case 5:
				cout << endl;
				break;

			default:
				cout << endl << "Error! Default switch in manager menu!" << endl << endl;
				break;
			}

			break;

		default:
			break;
		}
	}

	return 0;
}