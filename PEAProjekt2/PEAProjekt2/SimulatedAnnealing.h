#pragma once

#include "matrix.h"
#include "VectorMatrix.h"

class SimulatedAnnealing {
	vector_matrix neighborhoodMatrix;
	vector<int> path;
	// bool *visited;
	int pathCost = MAXINT;
	// float temperature = 1.0;
	int iterations;
	float initialTempCoefficient;
	int warunekZatrzymania;
public:
	SimulatedAnnealing();
	SimulatedAnnealing(vector_matrix m);
	SimulatedAnnealing(vector_matrix m, int iter, float tempC, int intIter);
	vector<int> getRandomNeigboringSolution(vector<int> path);
	int calculatePathCost(vector<int> path);
	void find_path(vector_matrix m, int iterations, float tempCoefficient);
	void print_result();
	vector <int> getPath();
	int getIterations();
	int getInternalIterations();
	float getInitialTempCoefficient();
};