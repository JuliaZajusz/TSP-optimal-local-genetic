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
	GeneticForIslandMethod gen = *new GeneticForIslandMethod(n, populationTab.size(), populationTab.size()/2, 1, 20, 10, populationTab, threadNumber == 1 ? true: false); 
	//    vector_matrix m,
																																  //    int populationSize,
																																  //	int parentPopulationSize,
																																  //	int generationsNumber,
																																  //	int mutationsProbability,
																																  //	int swapsInMutation,
																																  //	vector<individual> populationTab
// gen.print_result();
	if (threadNumber == 0)
	{
		if (bestIndividual.cost < gen.finalCost)
		{
			bestIndividual.cost = gen.finalCost;
			bestIndividual.genotyp = gen.finalPath;
		}
	}

	if(threadNumber == 1)
	{
		if (bestIndividual1.cost < gen.finalCost)
		{
			bestIndividual1.cost = gen.finalCost;
			bestIndividual1.genotyp = gen.finalPath;
		}
	}
	if (threadNumber == 2)
	{
		if (bestIndividual2.cost < gen.finalCost)
		{
			bestIndividual2.cost = gen.finalCost;
			bestIndividual2.genotyp = gen.finalPath;
		}
	}
	// if(bestIndividual.cost < gen.finalCost)
	// {
	// 	bestIndividual.cost = gen.finalCost;
	// 	bestIndividual.genotyp = gen.finalPath;
	// }

	// return gen.getPopulationTab()[rand() % populationTab.size()];
	return gen.getPopulationTab();
}


IslandMethod::IslandMethod(vector_matrix m)
{
	int populationSize = 50;
	neighborhoodMatrix = m;
	populationTab = GenerateBeginningPopulation(populationSize);
	find_path();
}


int IslandMethod::find_path()
{
	int generations = 10;
	int islands = 2;
	vector<individual> data = populationTab;
	size_t const half_size = data.size() / 2;
	vector<individual> lowHalf(data.begin(), data.begin() + half_size);
	vector<individual> lowHalfSingle(data.begin(), data.begin() + half_size);
	vector<individual> highHalf(data.begin() + half_size, data.end());

	{
		// findMin(exampleData1);

		// thread first(doGenetic, neighborhoodMatrix, 50, lowHalf);
		// thread second(doGenetic, neighborhoodMatrix, 50, highHalf);  // spawn new thread that calls findMin(highHalf)

		// future<individual> firstRet = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, lowHalf);
		// future<individual> secondRet = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, highHalf);
	}

	for (int i = 0; i < generations; i++)
	{
		cout << "Generacja " << i << endl;
		// {cout << "populationIsland_1: " << endl;
		// for (int j = 0; j < lowHalf.size(); j++)
		// {
		// 	cout << j << ": " << endl;
		// 	for (int k = 0; k < lowHalf[j].genotyp.size(); k++)
		// 	{
		// 		cout << lowHalf[j].genotyp[k] << " ";
		// 	}
		// 	cout << endl;
		// }
		// cout << endl;
		// cout << endl;
		// }

		future<vector<individual>> firstRetSingle = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, lowHalfSingle, 0);
		future<vector<individual>> firstRet = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, lowHalf, 1);
		future<vector<individual>> secondRet = async(&IslandMethod::doGenetic, this, neighborhoodMatrix, 50, highHalf, 2);

		int migratingUnit_1_Idx = rand() % half_size;
		int migratingUnit_2_Idx = rand() % half_size;

		lowHalf = firstRet.get();
		lowHalfSingle = firstRetSingle.get();
		highHalf = secondRet.get();

		cout << "migratingUnit_1_Idx: " << migratingUnit_1_Idx << endl;;
		cout << "migratingUnit_2_Idx: " << migratingUnit_2_Idx << endl;
		
		cout << "migratingUnit_1: " << lowHalf[migratingUnit_1_Idx].cost << endl;
		for (int j = 0; j < lowHalf[migratingUnit_1_Idx].genotyp.size(); j++)
		{
			cout << lowHalf[migratingUnit_1_Idx].genotyp[j] << " ";
		}
		cout << endl;
		
		
		cout << "migratingUnit_2: " << highHalf[migratingUnit_2_Idx].cost << endl;
		for (int j = 0; j < highHalf[migratingUnit_2_Idx].genotyp.size(); j++)
		{
			cout << highHalf[migratingUnit_2_Idx].genotyp[j] << " ";
		}
		cout << endl;
		individual tmp = lowHalf[migratingUnit_1_Idx];
		lowHalf[migratingUnit_1_Idx] = highHalf[migratingUnit_2_Idx];
		highHalf[migratingUnit_2_Idx] = tmp;

		cout << endl;
		cout << "najlepszySingle: " << bestIndividual.cost << endl << endl;
		cout << "najlepszy1: " << bestIndividual1.cost << endl << endl;
		cout << "najlepszy2: " << bestIndividual2.cost << endl << endl;
	}



	return 0;
}



vector<individual> IslandMethod::GenerateBeginningPopulation(int populationSize)
{
	cout << "poczatek GenerateBeginningPopulation" << endl;
	vector<individual> tab(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		vector<int> tmpTab(neighborhoodMatrix.nVertices);
		GenerateRandomPermutation(tmpTab);
		tab[i].genotyp = tmpTab;
		tab[i].cost = calculatePathCost(tmpTab);
		tmpTab.clear();
	}
	cout << "koniec GenerateBeginningPopulation" << endl;
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