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

	Movie m1("Finding Nemo", "Sci-Fi", 2000, 120);
	Movie m2("The Conjuring", "Horror", 2013, 180);
	Movie m3("American Pie", "Comedy", 1995, 150);

	viewer.ClearFile();

	viewer.AddMovieToFile(m1);
	viewer.AddMovieToFile(m2);
	viewer.AddMovieToFile(m3);

	viewer.ReadMovieFromFile();

	viewer.PrintWatchlist();

	exit(0);

	//int choice = 1;
	//while (choice!=NULL)
	//{
	//	cout << "Welcome to BambaFlix!" << "\n" << "\n";
	//	cout << "1. Viewer" << "\n" << "2. Manager" << "\n" << "0. Exit" << "\n" << "\n";
	//	cin >> choice; // Throw exceptions later
	//	cout << "\n";
	//	switch (choice)
	//	{
	//	case 0:
	//		exit(0);
	//		break;

	//	case 1:

	//		if (viewer.CheckIfEmpty() == true) // Place in ViewerMenu() later
	//		{
	//			viewer.SetId();
	//			viewer.SetFirstName();
	//			viewer.SetDayOfBirth();
	//		}

	//		cout << "\n" << "Welcome " + viewer.getFirstName() << "!" << "\n" << "\n";
	//		cout << "1. Add Series To Watchlist" << "\n";
	//		cout << "2. Add Movie To Watchlist" << "\n";
	//		cout << "3. Search Media By Name" << "\n";
	//		cout << "4. Watch Series From Watchlist" << "\n";
	//		cout << "5. Watch Movie From Watchlist" << "\n";
	//		cout << "6. Delete Series From Watchlist" << "\n";
	//		cout << "7. Delete Movie From Watchlist" << "\n";
	//		cout << "8. Back to Main Menu" << "\n" << "\n";
	//		cout << "Choose an action: ";

	//		cin >> choice;
	//		switch (choice)
	//		{
	//		default:
	//			cout << "\n" << "Error! Default switch in viewer menu!" << "\n" << "\n";
	//			break;
	//		}

	//		break;

	//	case 2:

	//		if (manager.CheckIfEmpty() == true)
	//		{
	//			manager.SetId();
	//			manager.SetFirstName();
	//			manager.SetDayOfBirth();
	//		}

	//		cout << "\n" << "Welcome " + manager.getFirstName() << "!" << "\n" << "\n";
	//		cout << "1. Add Series To The Database" << "\n";
	//		cout << "2. Add Movie To The Database" << "\n";
	//		cout << "3. Delete Media By Search" << "\n";
	//		cout << "4. Delete Media By Category" << "\n";
	//		cout << "5. Back To Main Menu" << "\n" << "\n";

	//		cin >> choice;
	//		switch (choice)
	//		{
	//		default:
	//			cout << "\n" << "Error! Default switch in manager menu!" << "\n" << "\n";
	//			break;
	//		}

	//		break;

	//	default:
	//		break;
	//	}
	//}

	return 0;
}