#pragma once
#include "GeneticForIslandMethod.h"

class IslandMethod
{
	vector_matrix neighborhoodMatrix;
	vector<individual> populationTab;
	individual bestIndividual = individual();
	// individual bestIndividual1 = individual();
	// individual bestIndividual2 = individual();
	int islands;
	int populationSize;
	int generations;
	vector<individual> bestIndividuals;
	int migrators;

public:
	IslandMethod(vector_matrix m, int populationSize, int generations, int islands, int migrators);
	vector<individual> GenerateBeginningPopulation(int populationSize);
	void GenerateRandomPermutation(vector<int> & tab);
	void swapS(vector<int>& permutation, int i, int j);
	int find_path();
	vector<individual> doGenetic(vector_matrix n, int populationSize, vector<individual> populationTab, int threadNumber);
	int calculatePathCost(vector<int> path);
	individual getBest(vector<individual> individuals);
};

