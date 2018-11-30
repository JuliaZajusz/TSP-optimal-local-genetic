#pragma once
#include "Matrix.h"
#include <vector>

class brute_force {
private:
	int pathCost = MAXINT;     //wagaSciezki
	int *path;                 //sciezka
	matrix neighborhoodMatrix;
public:
	explicit brute_force(matrix m);
	int calculate_costs(int* verticles);
	void find_path();
	bool check_path_consistency(int *verticles);
	void print_result();
	vector<int> getPath();
	int getCost();
};
