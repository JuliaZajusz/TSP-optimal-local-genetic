#include <sstream> 
#include <iostream>
using namespace std;

int* extractIntegerWords(string str)
{
	stringstream ss;
	ss << str;
	string temp;
	int found;
	int * array = new int[1];
	while (!ss.eof()) {
		ss >> temp;

		/* Checking the given word is integer or not */
		if (stringstream(temp) >> found)
			array[sizeof(array)] = found;
		/* To save from space at the end of string */
		temp = "";
	}
	return array;
}