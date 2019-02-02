// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>
#include <algorithm>
#include "IslandMethod.h"
#include <future>
using namespace std;

/* uruchomienie pomiaru czasu */
void IslandMethod::startCounter() {
	counterStart = chrono::steady_clock::now();
}

/* zwraca czas pomiaru podany w ms */
double IslandMethod::getCounter() {
	auto end = chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end - counterStart).count() * 1000;
}

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
	// rozpoczęcie algorytmu – start odliczania
	startCounter();

	for(int i =0; i<islands; i++)
	{
		islandsData[i] = vector<individual> (data.begin() + i * island_population_size, data.begin() + (i+1)* island_population_size);
	}

	for (int h = 0; h < generations; h++)
	{
		// if(h%10==0 && getCounter()> 10000)
		if(getCounter()> 10000)
		{
			return 0;
		}
		// cout << "Generacja " << h << endl;
		// cout << "Najlepszy: " << bestIndividual.cost << endl;
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
				// migratorsIdxes[j] = rand() % island_population_size; //losowy osobnik migruje
				migratorsIdxes[j] = j; //najlepszy osobnik migruje
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
		// cout << endl;
		//
		// for (int i = 0; i < islands; i++)
		// {
		// 	cout << "bestIndividuals["<<i<<"]: " << bestIndividuals[i].cost << endl << endl;
		// }
		// cout << "najlepszy: " << getBest(bestIndividuals).cost << endl << endl;

		bestIndividual = bestIndividuals[0];
		for (int i = 0; i < islands; i++)
		{
			if (bestIndividuals[i].cost < bestIndividual.cost) {
				bestIndividual = bestIndividuals[i];
			}
		}
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

individual IslandMethod::getBestIndividual()
{
	return bestIndividual;
}


vector<individual> IslandMethod::GenerateBeginningPopulation(int populationSize)
{
	vector<individual> tab(populationSize);
		for (int i = 0; i < populationSize && i<neighborhoodMatrix.nVertices; i++)
		{
			vector<int> tmpTab = getRandomGreedyPath(i);
			tab[i].genotyp = tmpTab;
			tab[i].cost = calculatePathCost(tmpTab);
			tmpTab.clear();
		}
	for (int i = neighborhoodMatrix.nVertices; i < populationSize; i++)
	{
		vector<int> tmpTab(neighborhoodMatrix.nVertices);
		GenerateRandomPermutation(tmpTab);
		tab[i].genotyp = tmpTab;
		tab[i].cost = calculatePathCost(tmpTab);
		tmpTab.clear();
	}
	return tab;
}

vector<int> IslandMethod::getRandomGreedyPath(int v)
{
	vector <int> cPath(neighborhoodMatrix.nVertices, -10);
	int ** tmpTab = new int*[neighborhoodMatrix.nVertices];

	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		tmpTab[i] = new int[neighborhoodMatrix.nVertices];
	}
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
		{
			tmpTab[i][j] = neighborhoodMatrix.neighborhoodMatrix[i][j];
		}
	}


	int tmp_min = 999999999;
	int tmp_index;

	cPath[0] = v;
	// cPath[neighborhoodMatrix.nVertices] = v;

	for (int X = 0; X < neighborhoodMatrix.nVertices; X++)
		tmpTab[X][v] = MAXINT;

	for (int N = 1; N < neighborhoodMatrix.nVertices; N++)
	{
		for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
			if (tmpTab[v][j] < tmp_min)
			{
				tmp_min = tmpTab[v][j];
				tmp_index = j;
			}
		for (int X = 0; X < neighborhoodMatrix.nVertices; X++)
			tmpTab[X][tmp_index] = MAXINT;
		v = tmp_index;
		tmp_min = MAXINT;

		cPath[N] = v;
	}


	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
		delete[] tmpTab[i];
	delete[] tmpTab;

	return cPath;
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