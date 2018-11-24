#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int PLACEHOLDER_VALUE = -10;
const int MAX_SIZE = 30;
const int MAXINT = 2147483647;

class matrix {
public:
	int nVertices;
	int neighborhoodMatrix[MAX_SIZE][MAX_SIZE];
	matrix();
	matrix(int nVertices);
	bool loadFromFile(std::string filename);
	void printNeighborhoodMatrix();
};

#endif