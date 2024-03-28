#pragma once
#include <iostream>
using namespace std;

static class Exceptions
{
public:

	static void CheckMenuInt(int min, int max, string input) throw(out_of_range, invalid_argument);

	static int GetMenuInt(int choice, int min, int max) throw (out_of_range, invalid_argument);

	static int GetOpenInt(int num, int min, int max) throw(out_of_range, invalid_argument);
};