#pragma once
#include <iostream>
using namespace std;

static class Exceptions
{
public:

	static void OperatorCheck(const std::string& input);

	static void CheckInt(int min, int max, string input) throw(out_of_range, invalid_argument);

	static int GetMenuInt(int choice, int min, int max) throw (out_of_range, invalid_argument);

	static void CheckString(string input, unsigned int min, unsigned int max, bool stringOnly) throw(out_of_range, invalid_argument);

	static void CheckChar(string input);
};