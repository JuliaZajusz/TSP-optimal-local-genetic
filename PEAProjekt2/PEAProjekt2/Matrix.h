#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
#include <string>
class vector_matrix;
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
	matrix(vector_matrix m);
	bool loadFromFile(std::string filename);
	void printNeighborhoodMatrix();
};

#endif