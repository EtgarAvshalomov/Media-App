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
	//Viewer Ben(0,0,0,0,"","");
	//int who=1;
	//while (who!=NULL)
	//{


	//	cout << "Welcome to BambaFlix!" << "\n";
	//	cout << "1.Viewer" << "\n" << "2.Manager" << "\n" << "0.EXIT" << "\n";
	//	cin >> who;
	//	switch (who)
	//	{
	//	case 0:
	//		exit(0);
	//		break;
	//	case 1:
	//		if (Ben.CheckIfEmpty() == true)
	//		{
	//			Ben.SetId();
	//			Ben.SetDayOfBirth();
	//			Ben.SetFirstName();
	//		}
	//		else
	//		{
	//			int action = 0;
	//			cout << "Welcome " + Ben.getFirstName()<<"\n";
	//			cout << "1.Add Series to Watch list" << "\n" << "2.Add Movie to Watch list" << "\n" << "3.Search Media by name" << "\n" << "4.Watch a Movie From watch list" << "\n" << "5.Watch a Series From watch list" << "\n" << "6.Delete a Series From watch list" << "\n" << "7.Delete a Movie From watch list" << "\n" << "8.Delete a Series From watch list" << "\n" << "9.Back To main menu";
	//			cout << "Choose an action: ";
	//			cin >> action;
	//			switch (action)
	//			{
	//			default:
	//				cout << "ya homo";
	//		
	//			}
	//		}

	//	case 2:
	//		break;
	//	default:who = NULL;
	//		break;
	//	}
	//}

	Movie m("Finding Nemo", "Adventure", 2002, 15);

	Viewer v(211390869, 15, 5, 2000, "Johnny", "Cage");

	v.AddMovieToFile(m);

	v.ReadMovieFromFile();

	return 0;
}