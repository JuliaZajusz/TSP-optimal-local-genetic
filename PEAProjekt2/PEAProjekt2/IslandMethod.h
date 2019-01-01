#pragma once
#include "Genetic.h"

class IslandMethod
{
	vector_matrix neighborhoodMatrix;
	vector<individual> populationTab;
public:
	IslandMethod(vector_matrix m);
	vector<individual> GenerateBeginningPopulation(int populationSize);
	void GenerateRandomPermutation(vector<int> & tab);
	void swapS(vector<int>& permutation, int i, int j);
	int find_path();
};

