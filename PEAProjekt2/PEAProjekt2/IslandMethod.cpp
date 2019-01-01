// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <vector>
#include <algorithm>
#include "IslandMethod.h"
using namespace std;

// vector<int> exampleData1 = { 8,4,2,7,1,4,9,3,5,6 };

//
// int findMin(vector<int> vec)
// {
// 	cout << *min_element(vec.begin(), vec.end()) << endl;
// 	return *min_element(vec.begin(), vec.end());
// }

void doGenetic(vector_matrix n, int populationSize,  vector<individual> populationTab)
{
	Genetic gen = *new Genetic(n, populationTab.size(), populationTab.size()/2, 10, 20, 10, populationTab);
	gen.print_result();
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
	vector<individual> data = populationTab;
	size_t const half_size = data.size() / 2;
	vector<individual> lowHalf(data.begin(), data.begin() + half_size);
	vector<individual> highHalf(data.begin() + half_size, data.end());

	// findMin(exampleData1);

	thread first(doGenetic, neighborhoodMatrix, 50, lowHalf);
	thread second(doGenetic, neighborhoodMatrix, 50, highHalf);  // spawn new thread that calls findMin(highHalf)

	cout << "main, foo and bar now execute concurrently...\n";

	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	cout << "foo and bar completed.\n";

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
		tmpTab.clear();
	}
	cout << "koniec GenerateBeginningPopulation" << endl;
	return tab;
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