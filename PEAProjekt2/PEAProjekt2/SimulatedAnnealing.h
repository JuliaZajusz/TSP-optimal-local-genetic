#pragma once

#include "matrix.h"
#include "VectorMatrix.h"
#include <chrono>

class SimulatedAnnealing {
	vector_matrix neighborhoodMatrix;
	vector<int> path;
	int pathCost = MAXINT;
	int iterations;
	float initialTempCoefficient;
	int warunekZatrzymania;
	std::chrono::steady_clock::time_point counterStart;

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
	void startCounter();
	double getCounter();
	vector<int> getRandomGreedyPath(int v);
};
