#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class vector_matrix {
public:
	int nVertices;
	std::vector<vector<int>> neighborhoodMatrix;
	vector_matrix();
	vector_matrix(int vertices);
	vector_matrix(int **matrix, int vertices);
	~vector_matrix();
	bool loadFromFile(std::string filename);
	void printNeighborhoodMatrix();
};