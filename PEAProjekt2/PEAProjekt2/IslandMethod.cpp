// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>
#include <algorithm>
#include "IslandMethod.h"
#include <future>
using namespace std;

// vector<int> exampleData1 = { 8,4,2,7,1,4,9,3,5,6 };

//
// int findMin(vector<int> vec)
// {
// 	cout << *min_element(vec.begin(), vec.end()) << endl;
// 	return *min_element(vec.begin(), vec.end());
// }

vector<individual> IslandMethod::doGenetic(vector_matrix n, int populationSize,  vector<individual> populationTab, int threadNumber)
{
	GeneticForIslandMethod gen = *new GeneticForIslandMethod(n, populationTab.size(), populationTab.size()/2, 1, 20, 10, populationTab, false); 
	// GeneticForIslandMethod gen = *new GeneticForIslandMethod(n, populationTab.size(), populationTab.size()/2, 1, 20, 10, populationTab, true); 
	// GeneticForIslandMethod gen = *new GeneticForIslandMethod(n, populationTab.size(), populationTab.size()/2, 1, 20, 10, populationTab, threadNumber == 1 ? true: false); 
	//    vector_matrix m,
																																  //    int populationSize,
																																  //	int parentPopulationSize,
																																  //	int generationsNumber,
																																  //	int mutationsProbability,
																																  //	int swapsInMutation,
																																  //	vector<individual> populationTab
// gen.print_result();

	// if(threadNumber ==0)
	// {
	// 	bestIndividual.cost = gen.finalCost;
	// 	bestIndividual.genotyp = gen.finalPath;
	// }
		bestIndividuals[threadNumber].cost = gen.finalCost;
		bestIndividuals[threadNumber].genotyp = gen.finalPath;
	return gen.getPopulationTab();
}


IslandMethod::IslandMethod(vector_matrix m, int populationSize, int generations, int islands, int migrators)
{	
	neighborhoodMatrix = m;
	this->populationSize = populationSize;
	this->generations = generations;
	this->islands = islands;
	this->migrators = migrators;
	populationTab = GenerateBeginningPopulation(populationSize);
	bestIndividuals = vector<individual>(islands);
	find_path();
}


int IslandMethod::find_path()
{
	vector<individual> data = populationTab;
	vector<vector<individual>> islandsData = vector<vector<individual>>(islands);
	vector<future<vector<individual>>> futures= vector<future<vector<individual>>>(islands);
	vector<vector<int>> migratingUnitIdx = vector<vector<int>>(islands, vector<int>(migrators));
	size_t const island_population_size = data.size() / islands;

	// vector<individual> lowHalfSingle(data.begin(), data.begin() + island_population_size);

	for(int i =0; i<islands; i++)
	{
		islandsData[i] = vector<individual> (data.begin() + i * island_population_size, data.begin() + (i+1)* island_population_size);
	}

	for (int h = 0; h < generations; h++)
	{
		cout << "Generacja " << h << endl;
		// {
		// 	cout << "populationIsland_1: " << endl;
		// for (int j = 0; j < island_population_size; j++)
		// {
		// 	cout << j << ": " << endl;
		// 	for (int k = 0; k < islandsData[0][j].genotyp.size(); k++)
		// 	{
		// 		cout << islandsData[0][j].genotyp[k] << " ";
		// 	}
		// 	cout << endl;
		// }
		// cout << endl;
		// cout << endl;
		// }
		// {
		// 	cout << "populationIsland_2: " << endl;
		// 	for (int j = 0; j < island_population_size; j++)
		// 	{
		// 		cout << j << ": " << endl;
		// 		for (int k = 0; k < islandsData[1][j].genotyp.size(); k++)
		// 		{
		// 			cout << islandsData[1][j].genotyp[k] << " ";
		// 		}
		// 		cout << endl;
		// 	}
		// 	cout << endl;
		// 	cout << endl;
		// }

		// future<vector<individual>> firstRetSingle = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, lowHalfSingle, 0);
		// lowHalfSingle = firstRetSingle.get();
		// cout << "najlepszySingle: " << bestIndividual.cost << endl << endl;
		
		for (int i = 0; i < islands; i++)
		{
			futures[i] = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, islandsData[i], i);
			vector<int> migratorsIdxes(migrators);
			for (int j = 0; j < migrators; j++)
			{
				migratorsIdxes[j] = rand() % island_population_size;
			}
			migratingUnitIdx[i] = migratorsIdxes;
			islandsData[i] = futures[i].get();
		}

		// for (int i = 0; i < islands; i++)
		// {
		// 	cout << "migratingUnitIdx[" << i << "]: ";
		// 	for (int j = 0; j < migrators; j++)
		// 	{
		// 		cout<< migratingUnitIdx[i][j]<<", ";
		// 	}
		// 	cout << endl;
		// }
		
		//dla każdej wyspy i wybierz jednostki migrujące j i przenieś je do wyspy obok
		vector<individual> migrator0(migrators);
		for (int j = 0; j < migrators; j++)
		{
			migrator0[j] = islandsData[0][migratingUnitIdx[0][j]];
		}
		for (int i = 0; i < islands -1; i++)  
		{
			for (int j = 0; j < migrators; j++)
			{
				individual tmp = islandsData[i][migratingUnitIdx[i][j]];
				islandsData[i][migratingUnitIdx[i][j]] = islandsData[i + 1][migratingUnitIdx[i + 1][j]];
				islandsData[i + 1][migratingUnitIdx[i + 1][j]] = tmp;
			}
		}
		for (int j = 0; j < migrators; j++)
		{
			islandsData[islands - 1][migratingUnitIdx[islands - 1][j]] = migrator0[j];
		}
		cout << endl;

		for (int i = 0; i < islands; i++)
		{
			cout << "bestIndividuals["<<i<<"]: " << bestIndividuals[i].cost << endl << endl;
		}
		cout << "najlepszy: " << getBest(bestIndividuals).cost << endl << endl;
	}
	return 0;
}

individual IslandMethod::getBest(vector<individual> individuals)
{
	individual best = individuals[0];
	for (int i = 1; i < individuals.size(); i++)
	{
		if (best.cost > individuals[i].cost) {
			best = individuals[i];
		}
	}
	return best;
}



vector<individual> IslandMethod::GenerateBeginningPopulation(int populationSize)
{
	vector<individual> tab(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		vector<int> tmpTab(neighborhoodMatrix.nVertices);
		GenerateRandomPermutation(tmpTab);
		tab[i].genotyp = tmpTab;
		tab[i].cost = calculatePathCost(tmpTab);
		tmpTab.clear();
	}
	return tab;
}

int IslandMethod::calculatePathCost(vector<int> path)
{
	int cost = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size() - 1]][path[0]];
	return cost;
}

void IslandMethod::GenerateRandomPermutation(vector<int>& tab)
{
	for (int i = 0; i < tab.size(); i++)
	{
		tab[i] = i;
	}

	for (int i = 0; i < tab.size(); i++)
	{
		int r = rand() % (tab.size() - i);
		swapS(tab, r, tab[i + r]);
	}
}

void IslandMethod::swapS(vector<int>& permutation, int i, int j)
{
	int temp = permutation[i];
	permutation[i] = permutation[j];
	permutation[j] = temp;
}