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

			viewer.ViewerMenu();
			break;

		case 2:

			manager.ManagerMenu();
			break;

		default:
			break;
		}
	}

	return 0;
}