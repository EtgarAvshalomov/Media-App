#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include "Viewer.h"
#include "Manager.h"
#include <string>
#include "Exceptions.h"
#define RESET "\033[0m"
#define RED "\033[91m" 
#define CYAN "\033[96m"

#pragma comment(lib, "winmm.lib")
using namespace std;

int main()
{
	PlaySound(TEXT("RiveR - Solo"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC); // Fitgirl //

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
			cout << endl << "Cya! ;D" << endl;
			exit(0);
			break;

		case 1:
			cout << CYAN;
			viewer.ViewerMenu();
			break;

		case 2:
			cout << RED;
			manager.ManagerMenu();
			break;

		default:
			cout << endl << "Default switch in main menu" << endl;
			break;
		}
	}

	return 0;
}