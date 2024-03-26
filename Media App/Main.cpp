#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include "Viewer.h"
#include "Manager.h"

#pragma comment(lib, "winmm.lib")
using namespace std;

int main()
{
	PlaySound(TEXT("RiveR - Solo.wav"), NULL, SND_FILENAME | SND_ASYNC); // Fitgirl

	Viewer viewer(0, 0, 0, 0, "", "");
	Manager manager(0, 0, 0, 0, "", "");

	int choice = 1;
	while (choice != NULL)
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