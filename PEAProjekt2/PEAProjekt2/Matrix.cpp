#include "matrix.h"
#include <sstream> 
#include "VectorMatrix.h"
//#include <iostream>
using namespace std;

matrix::matrix()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			neighborhoodMatrix[i][j] = PLACEHOLDER_VALUE;
		}
	}
}

matrix::matrix(int vertices)
{
	nVertices = vertices;

	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {

			if(i>= vertices || j>=vertices)
			{
				neighborhoodMatrix[i][j] = PLACEHOLDER_VALUE;
			} else
			{
				int x;
				if (i == j)
				{
					x = 0;
				}
				else
				{
					x = rand() % 100;
				}
				neighborhoodMatrix[i][j] = x;
			}
			
		}
	}
}

matrix::matrix(vector_matrix m)
{
	nVertices = m.nVertices;

	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {

			if (i >= nVertices || j >= nVertices)
			{
				neighborhoodMatrix[i][j] = PLACEHOLDER_VALUE;
			}
			else
			{
				neighborhoodMatrix[i][j] = m.neighborhoodMatrix[i][j];
			}

		}
	}
}

bool matrix::loadFromFile(std::string filename)
{
	std::fstream file;
	file.open(filename.c_str());
	if (!file.good()) {
		cout << "Nazwa pliku jest nieprawidlowa.\n";
		return false;
	}
	int matrixSize;
	file >> matrixSize;
	cout << matrixSize << endl;
	nVertices = matrixSize;
	while (true) {
		if (file.good()) {
			for (int i = 0; i < matrixSize; i++) {
				for (int j = 0; j < matrixSize; j++) {
					int x;
					file >> x;
					neighborhoodMatrix[i][j] = x;
				}
			}
		}
		else {
			break;
		}
	}
	file.close();
	return true;
}

void matrix::printNeighborhoodMatrix()
{
	for (int i = 0; i < MAX_SIZE; i++) {
		if (neighborhoodMatrix[i][0] == PLACEHOLDER_VALUE) {
			break;
		}
		for (int j = 0; j < MAX_SIZE; j++) {
			if (neighborhoodMatrix[i][j] == PLACEHOLDER_VALUE) {
				break;
			}
			std::cout << neighborhoodMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
