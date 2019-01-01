#pragma once
#include "matrix.h"
#include <vector>
#include "VectorMatrix.h"

class Genetic
{
private:
	typedef struct  individual {
		// int * genotyp;
		vector<int> genotyp;
		int cost;
	};

	vector_matrix neighborhoodMatrix;
	vector<int> path;
	int pathCost = MAXINT;

	// int N;
	// int ** tab;
	// int dimension;
	// int * parameters;

	int populationSize;

	int parentPopulationSize;
	int generationsNumber;
	int mutationsProbability;
	int swapsInMutation;
	vector<individual> populationTab;

	int * parentsTab;

public:

	vector<int> finalPath;
	int finalCost;
	Genetic(vector_matrix m);
	~Genetic();
	// void GenerateRandomPermutation(vector<int> tab);
	void GenerateRandomPermutation(vector<int> & tab);
	void GeneticAlg();
	void GenerateBeginningPopulation();
	void swapS(vector<int>& permutation, int i, int j);
	void ChooseParents(int parentPopulationSize);
	individual Crossing(individual parent1, individual parent2, int rand1, int rand2);
	void CrossingImplementation();
	void Mutation(individual & child);
	void Sortowanie(vector<individual> & population, int size);
	void NewGeneration();

	void SortPopulation(vector<individual>  & population);

	int calculatePathCost(vector<int> path);
	void print_result();
};
