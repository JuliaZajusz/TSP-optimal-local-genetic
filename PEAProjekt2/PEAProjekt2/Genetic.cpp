#include "Genetic.h"
#include <time.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */

Genetic::Genetic(vector_matrix m)
{
	neighborhoodMatrix = m;

	populationSize = 50;//////// populationSize;
	parentPopulationSize = 25;////////// parentPopulationSize;
	generationsNumber = 10; //generacje
	mutationsProbability = 20; //mutacje %
	swapsInMutation = 10;//ile swapów w mutacji

	finalPath = vector<int>(neighborhoodMatrix.nVertices);
	populationTab = vector< individual>(populationSize);
	cout << "tu\n";
	GeneticAlg();
	// find_path(neighborhoodMatrix, iterations, initialTempCoefficient);
}


Genetic::~Genetic()
{
	delete[] parentsTab;
}

void Genetic::GeneticAlg()
{
	cout << "geneticAlg" << endl;
	srand(time(NULL));
	// fillParameters(parameters);
	GenerateBeginningPopulation();

	NewGeneration();

	//	ChooseParents(parentPopulationSize);
	//
	//	/*for (int i = 0; i < parentPopulationSize; i++)
	//	{
	//		std::cout << parentsTab[i] << std::endl;
	//	}*/
	//
	//	CrossingImplementation();
	//
	//	SortPopulation();
	//
	//	ReducePopulation();
		//Crossing();
}


void Genetic::GenerateBeginningPopulation()
{

	for (int i = 0; i < populationSize; i++)
	{
		vector<int> tmpTab(neighborhoodMatrix.nVertices);

		GenerateRandomPermutation(tmpTab);
		populationTab[i].genotyp = tmpTab;
	}

	// for (int i = 0; i < populationSize; i++)
	// {
	// 	for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
	// 	{
	// 		std::cout << populationTab[i].genotyp[j] << " ";
	// 	}
	// 	std::cout << "DL: " << calculatePathCost(populationTab[i].genotyp);
	// 	std::cout << std::endl;
	// }
}

void Genetic::GenerateRandomPermutation(vector<int>& tab)
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

void Genetic::NewGeneration()
{
	for (int i = 0; i < generationsNumber; i++)
	{
		cout << "Generacja " << i << endl;
		ChooseParents(parentPopulationSize);

		CrossingImplementation();
		
		// SortPopulation();
		//
		// ReducePopulation();
	}
}

void Genetic::ChooseParents(int parentPopulationSize)
{
	parentsTab = new int[parentPopulationSize];
	// int * tmpTab = new int[populationSize];
	vector<int> tmpTab(populationSize);

	int iloscSwap = rand() % populationSize;
	for (int i = 0; i < populationSize; i++)
	{
		tmpTab[i] = i;
	}

	for (int i = 0; i < iloscSwap; i++)
	{
		int ra = rand() % populationSize;
		int ra2 = rand() % populationSize;
		swapS(tmpTab, ra, ra2);
	}

	for (int i = 0; i < parentPopulationSize; i++)
	{
		parentsTab[i] = tmpTab[i];
	}

	// delete[] tmpTab;
}

Genetic::individual Genetic::Crossing(individual parent1, individual parent2, int rand1, int rand2)
{
	individual child;
	child.genotyp = vector<int>(neighborhoodMatrix.nVertices);
	
	int * checkForRepeat = new int[neighborhoodMatrix.nVertices];
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		checkForRepeat[i] = 0;
	}
	
	for (int i = rand1; i < rand2; i++)				//œrodek
	{
		child.genotyp[i] = parent2.genotyp[i];
		checkForRepeat[child.genotyp[i]] = 1;
	}
	
	for (int i = 0; i < rand1; i++)				//pocz¹tek
	{
		int zm = parent1.genotyp[i];
	
		if (checkForRepeat[zm] == 0)
		{
			child.genotyp[i] = zm;
			checkForRepeat[zm] = 1;
		}
		else
		{
			child.genotyp[i] = -510;
		}
	}
	
	for (int i = rand2; i < neighborhoodMatrix.nVertices; i++)			//koniec
	{
		int zm = parent1.genotyp[i];
	
		if (checkForRepeat[zm] == 0)
		{
			child.genotyp[i] = zm;
			checkForRepeat[zm] = 1;
		}
		else
		{
			child.genotyp[i] = -510;
		}
	}
	
	int s = 0;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		if (child.genotyp[i] == -510)
		{
			for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
			{
				if (checkForRepeat[j] == 0)
				{
					child.genotyp[i] = j;
					checkForRepeat[j] = 1;
					break;
				}
			}
	
		}
	}
	delete[] checkForRepeat;
	return child;

	return parent1;
}

void Genetic::CrossingImplementation()  //rozmnazanie
{
	// individual * tmpIndividual = new individual[populationSize + 2 * (floor(parentPopulationSize / 2)) + 1];
	vector<individual> tmpIndividual = vector<individual>(populationSize +  2 * (floor(parentPopulationSize / 2)));

	for (int i = 0; i < populationSize; i++)
	{
		tmpIndividual[i] = populationTab[i];
		cout <<"i: "<<i<< endl;
		for(int j=0; j<neighborhoodMatrix.nVertices; j++)
		{
			cout << populationTab[i].genotyp[j] << " ";
		}
		cout << endl;
	}
	cout<< "liczba par rodzicow: " << floor(parentPopulationSize / 2) << endl;
	for (int i = 0; i < floor(parentPopulationSize / 2); i++)  //dla kazdej pary rodzicow
	{
		//tmpIndividual = vector<individual>(populationSize + 2 * (floor(parentPopulationSize / 2)));
		int crossPoint1 = rand() % (neighborhoodMatrix.nVertices - 1);
		int crossPoint2 = rand() % ((neighborhoodMatrix.nVertices - crossPoint1 - 1) + crossPoint1 + 1);
		// std::cout << i << " CS1: " << crossPoint1 << std::endl;					//TODO: do usuniecia
		// std::cout << "CS2: " << crossPoint2 << std::endl;					//TODO: do usuniecia

		cout <<"i: "<<  i<< endl;
		cout<<" "<< populationTab[parentsTab[2 * i]].genotyp[0] << " " << populationTab[parentsTab[(2 * i) + 1]].genotyp[0] << endl;

		individual a = Crossing(populationTab[parentsTab[2 * i]], populationTab[parentsTab[(2 * i) + 1]], crossPoint1, crossPoint2);  //dziecko1
		individual b = Crossing(populationTab[parentsTab[(2 * i) + 1]], populationTab[parentsTab[(2 * i)]], crossPoint1, crossPoint2);  //dziecko2
		Mutation(a);
		Mutation(b);
		tmpIndividual[populationSize + (2 * i)] = a;
		tmpIndividual[populationSize + ((2 * i) + 1)] = b;

		//std::cout << "Genotyp dzieci" << std::endl;
		/*for (int x = 0; x < dimension; x++)
		{

			std::cout << tmpIndividual[populationSize + ((2 * i) + 1)].genotyp[x] << " ";
		}
		std::cout << std::endl;

		for (int x = 0; x < dimension; x++)
		{

			std::cout << tmpIndividual[populationSize + (2 * i)].genotyp[x] << " ";
		}
		std::cout << std::endl;*/
	}
	cout << "po malej petli" << endl;
	// delete[] populationTab;
	//populationSize = populationSize + parentPopulationSize;
	//populationTab = vector<individual>(populationSize);

	cout << "prawie koniec" << endl;
	for (int i = 0; i < populationSize-1; i++)
	{
		populationTab[i] = tmpIndividual[i];
	
	}
	//tmpIndividual.clear();


	cout << "koniec" << endl;
}

void Genetic::Mutation(individual & child)
{
	int chance = rand() % 100;
	if (chance <= mutationsProbability)
	{
		// std::cout << "MUTACJAAAAAAA" << std::endl;
		for (int i = 0; i < swapsInMutation; i++)
		{
			int city1 = rand() % (neighborhoodMatrix.nVertices );
			int city2 = rand() % (neighborhoodMatrix.nVertices );
			// cout << city1 << " " << city2 << endl;
			swapS(child.genotyp, city1, city2);
		}
	}
	//
	// return child;
}



void Genetic::ReducePopulation()
{
	individual * tmpPopulation = new individual[populationSize];

	for (int i = 0; i < populationSize; i++)
	{
		tmpPopulation[i] = populationTab[i];
	}

	populationTab = vector<individual>(populationSize);
	for (int i = 0; i < populationSize; i++)
	{
		populationTab[i] = tmpPopulation[i];
	}

	finalPath = populationTab[0].genotyp;
	finalCost = populationTab[0].cost;
}



void Genetic::Sortowanie(vector<individual> populationTab, int size)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (populationTab[j].cost > populationTab[j + 1].cost)
				std::swap(populationTab[j], populationTab[j + 1]);

		}
	}
}

void Genetic::SortPopulation()
{
	int * costTab = new int[populationSize];

	for (int i = 0; i < populationSize; i++)
	{
		int koszt = calculatePathCost(populationTab[i].genotyp);
		populationTab[i].cost = koszt;

	}

	Sortowanie(populationTab, populationSize);

}










// int Genetic::CountPathLength(int* cityPermutation, int** tab, int dimension)
// {
// 	int sum = 0;
// 	for (int i = 0; i < dimension - 1; ++i)
// 	{
// 		sum += tab[cityPermutation[i]][cityPermutation[i + 1]];
// 	}
// 	sum += tab[cityPermutation[dimension - 1]][cityPermutation[0]];
// 	return sum;
// }

int Genetic::calculatePathCost(vector<int> path)
{
	int cost = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size() - 1]][path[0]];
	return cost;
}

void Genetic::swapS(vector<int>& permutation, int i, int j)
{
	// cout << "a" << endl;
	int temp = permutation[i];
	permutation[i] = permutation[j];
	permutation[j] = temp;
}


void Genetic::print_result()
{
	// cout << "Sciezka: " << endl;
	// for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	// {
	// 	cout << path[i] << " ";
	// }
	// cout << path[0] << endl;
	// cout << "wagaSciezki = " << calculatePathCost(path) << endl;
	// cout << endl;


	cout << "Sciezka: " << endl;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		cout << finalPath[i] << " ";
	}
	cout << finalPath[0] << endl;
	cout << "wagaSciezki = " << calculatePathCost(finalPath) << endl;
	cout << endl;
}