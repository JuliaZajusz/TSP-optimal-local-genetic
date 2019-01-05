#include "GeneticForIslandMethod.h"
#include <time.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <algorithm>


GeneticForIslandMethod::GeneticForIslandMethod(vector_matrix m,
	int populationSize,
	int parentPopulationSize,
	int generationsNumber,
	int mutationsProbability,
	int swapsInMutation,
	vector<individual> populationTab,
	bool print)
{
	neighborhoodMatrix = m;
	this->populationSize = populationSize;
	this->parentPopulationSize = parentPopulationSize;
	this->generationsNumber = generationsNumber;
	this->mutationsProbability = mutationsProbability;
	this->swapsInMutation = swapsInMutation;
	this->populationTab = populationTab;
	this->print = print;

	finalPath = vector<int>(neighborhoodMatrix.nVertices);
	find_path();
}

void GeneticForIslandMethod::find_path()
{
	for (int i = 0; i < generationsNumber; i++)
	{
		doNewGeneration(i);
	}
}

void GeneticForIslandMethod::doNewGeneration(int i)
{
	// ChooseParents(parentPopulationSize);
	ChooseParentsTournament(parentPopulationSize);
	CrossingImplementation();
}


void GeneticForIslandMethod::ChooseParents(int parentPopulationSize)  //zmienic na ruletke moze, albo turniej
{
	parentsTab = vector<int>(parentPopulationSize);
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
}

void GeneticForIslandMethod::ChooseParentsTournament(int parentPopulationSize)  //zmienic na ruletke moze, albo turniej
{
	parentsTab = vector<int>(parentPopulationSize);

	for (int i = 0; i < parentPopulationSize; i++)
	{
		int ra = rand() % populationSize;
		int ra2 = rand() % populationSize;
		if(populationTab[ra].cost <= populationTab[ra2].cost)
		{
			parentsTab[i] = ra;
		} else
		{
			parentsTab[i] = ra2;
		}
	}
}

individual GeneticForIslandMethod::Crossing(individual parent1, individual parent2, int rand1, int rand2)
{
	// std::cout << " CS1: " << rand1 << std::endl;			
	// std::cout << "CS2: " << rand2 << std::endl;				
	// std::cout << "parent1: ";				
	// for(int i =0; i<parent1.genotyp.size(); i++)
	// {
	// 	cout << parent1.genotyp[i] << " ";
	// }
	// cout << endl;
	//
	// std::cout << "parent2: ";
	// for (int i = 0; i < parent2.genotyp.size(); i++)
	// {
	// 	cout << parent2.genotyp[i] << " ";
	// }
	// cout << endl;
	// cout << endl;


	individual child;
	child.genotyp = vector<int>(neighborhoodMatrix.nVertices);

	int * checkForRepeat = new int[neighborhoodMatrix.nVertices];
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		checkForRepeat[i] = 0;
	}

	for (int i = rand1; i < rand2; i++)				//srodek
	{
		child.genotyp[i] = parent2.genotyp[i];
		checkForRepeat[child.genotyp[i]] = 1;
	}

	for (int i = 0; i < rand1; i++)				//poczatek
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

void GeneticForIslandMethod::CrossingImplementation()  //rozmnazanie
{
	vector<individual> tmpIndividual = vector<individual>(populationSize + 2 * (floor(parentPopulationSize / 2))); //utworzenie zmiennej dla populacji z dziecmi

	for (int i = 0; i < populationSize; i++)
	{
		tmpIndividual[i] = populationTab[i];  //przekopiowana cała populacja (50)
	}
	for (int i = 0; i < floor(parentPopulationSize / 2); i++)  //dla kazdej pary rodzicow utworz pare dzieci
	{
		int crossPoint1 = rand() % (neighborhoodMatrix.nVertices - 1);
		int crossPoint2 = rand() % (neighborhoodMatrix.nVertices - crossPoint1 - 1) + crossPoint1 + 1;

		individual a = Crossing(populationTab[parentsTab[2 * i]], populationTab[parentsTab[(2 * i) + 1]], crossPoint1, crossPoint2);  //dziecko1
		individual b = Crossing(populationTab[parentsTab[(2 * i) + 1]], populationTab[parentsTab[(2 * i)]], crossPoint1, crossPoint2);  //dziecko2
		Mutation(a);
		Mutation(b);
		tmpIndividual[populationSize + (2 * i)] = a;
		tmpIndividual[populationSize + ((2 * i) + 1)] = b;


		// cout << "i:" << i << " index: " << populationSize + (2 * i) << endl;
		// for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
		// {
		// 	cout << a.genotyp[j] << " ";
		// }
		// cout << endl;
		//
		// cout << "i:" << i << " index: " << populationSize + ((2 * i) + 1) << endl;
		// for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
		// {
		// 	cout << b.genotyp[j] << " ";
		// }
		// cout << endl;

	}

	SortPopulation(tmpIndividual);

	finalPath = tmpIndividual[0].genotyp;
	finalCost = tmpIndividual[0].cost;


	for (int i = 0; i < populationSize; i++)
	{
		populationTab[i] = tmpIndividual[i];

	}
	//tmpIndividual.clear();

}

void GeneticForIslandMethod::Mutation(individual & child)
{
	int chance = rand() % 100;
	if (chance <= mutationsProbability)
	{
		for (int i = 0; i < swapsInMutation; i++)
		{
			int city1 = rand() % (neighborhoodMatrix.nVertices);
			int city2 = rand() % (neighborhoodMatrix.nVertices);
			swapS(child.genotyp, city1, city2);
		}
	}
}

void GeneticForIslandMethod::Sortowanie(vector<individual> & population, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			if (population[j].cost > population[j + 1].cost)
				std::swap(population[j], population[j + 1]);
		}
	}
}


// bool Genetic::Sort(individual a, individual b)
// {
// 	return (a.cost < b.cost);
// }

void GeneticForIslandMethod::SortPopulation(vector<individual> & population)
{
	for (int i = 0; i < population.size(); i++)
	{
		int koszt = calculatePathCost(population[i].genotyp);
		population[i].cost = koszt;

	}
	Sortowanie(population, population.size());
	// using function as comp												
	// std::sort(population.begin(), population.end(), Genetic::Sort);


	// population.erase(unique(population.begin(), population.end()), population.end());
	 // cout << unique(population[0], population[0]).cost  << endl;
	 // std::unique(population[0], population[0]) ? cout << "true" << endl : cout << "false" << endl;

	 auto comp = [](const individual& lhs, const individual& rhs) {return lhs.cost == rhs.cost && lhs.genotyp == rhs.genotyp; };
	 auto last = std::unique(population.begin(), population.end(), comp);
	 population.erase(last, population.end());

	if (print) {
		cout << endl;
		cout << endl;
		{cout << "POPULACJA PO SORTOWANIU: " << endl;
		for (int j = 0; j < population.size(); j++)
		{
			cout << j << ": " << endl << population[j].cost << ",        ";
			for (int k = 0; k < population[j].genotyp.size(); k++)
			{
				cout << population[j].genotyp[k] << " ";
			}
			cout << endl;
		}
		cout << endl;
		cout << endl;
		}
	}
}




int GeneticForIslandMethod::calculatePathCost(vector<int> path)
{
	int cost = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size() - 1]][path[0]];
	return cost;
}

void GeneticForIslandMethod::swapS(vector<int>& permutation, int i, int j)
{
	int temp = permutation[i];
	permutation[i] = permutation[j];
	permutation[j] = temp;
}


void GeneticForIslandMethod::print_result()
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

vector<individual> GeneticForIslandMethod::getPopulationTab()
{
	return populationTab;
}
