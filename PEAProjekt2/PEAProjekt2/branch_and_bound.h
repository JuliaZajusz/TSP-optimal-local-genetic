#pragma once
#include "matrix.h"
#include "VectorMatrix.h"

class branch_and_bound {
	vector_matrix neighborhoodMatrix;
	int *path;
	bool *visited;
	int pathCost = MAXINT;
public:
	branch_and_bound();
	branch_and_bound(vector_matrix m);
	void save_path(int* currentPath);
	int first_minimum_value(vector_matrix towns, int nr);
	int second_minimum_value(vector_matrix towns, int i);
	void bnb_recursion(vector_matrix towns, int currentLowerBound, int currentWeight, int level, int* currentPath);
	void find_path(vector_matrix towns);
	void print_result();
	vector<int> getPath();
	int getCost();
};
