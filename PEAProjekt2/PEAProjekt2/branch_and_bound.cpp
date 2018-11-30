#include "branch_and_bound.h"
#include <iostream>

branch_and_bound::branch_and_bound()
{
	
}

branch_and_bound::branch_and_bound(vector_matrix m)
{
	neighborhoodMatrix = m;
	path = new int[neighborhoodMatrix.nVertices + 1];
	visited = new bool[neighborhoodMatrix.nVertices];
	find_path(m);
}

void branch_and_bound::save_path(int* currentPath)
{
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		path[i] = currentPath[i];
	}
	path[neighborhoodMatrix.nVertices] = currentPath[0];
}

int branch_and_bound::first_minimum_value(vector_matrix towns, int w)
{
	int min = MAXINT;
	for (int k = 0; k < neighborhoodMatrix.nVertices; k++)
	{
		if (towns.neighborhoodMatrix[w][k] < min && w != k)
		{
			min = towns.neighborhoodMatrix[w][k];
		}
	}
	return min;
}

int branch_and_bound::second_minimum_value(vector_matrix towns, int w)
{
	int first = MAXINT;
	int second = MAXINT;

	for (int k = 0; k < neighborhoodMatrix.nVertices; k++)
	{
		if (w == k)
		{
			continue;
		}
		if (towns.neighborhoodMatrix[w][k] <= first)
		{
			second = first;
			first = towns.neighborhoodMatrix[w][k];
		}
		else if (towns.neighborhoodMatrix[w][k] <= second && towns.neighborhoodMatrix[w][k] != first)
		{
			second = towns.neighborhoodMatrix[w][k];
		}
	}
	return second;
}

void branch_and_bound::bnb_recursion(vector_matrix towns, int currentLowerBound, int currentWeight, int level,
	int* currentPath)
{
	if (level == neighborhoodMatrix.nVertices)
	{
		//Sprawdzenie czy jest możliwość powrotu do wierzchołka startowego
		if (towns.neighborhoodMatrix[currentPath[level - 1]][ currentPath[0]] >0)
		{
			//Dodanie kosztu drogi powrotnej do dotychczasowego kosztu 
			int curr_res = currentWeight + towns.neighborhoodMatrix[currentPath[level - 1]][ currentPath[0]];

			//Aktualizacja najlepszego wyniku w przypadku znalezienia lepszego rozwiązania 
			if (curr_res < pathCost)
			{
				save_path(currentPath);
				pathCost = curr_res;
			}
		}
		return;
	}

	// Budowanie drzewa 
	// Przejścia przez wierzchołki grafu
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		if (towns.neighborhoodMatrix[currentPath[level - 1]][ i] >0 && visited[i] == false)
		{
			// Aktualna dolna granica kosztu w celu ewentualnego powrotu do wyższego poziomu
			int temp = currentLowerBound;
			currentWeight += towns.neighborhoodMatrix[currentPath[level - 1]][i];

			if (level == 1)
			{
				currentLowerBound -= ((first_minimum_value(towns, currentPath[level - 1]) + first_minimum_value(towns, i)) / 2);
			}
			else
			{
				currentLowerBound -= ((second_minimum_value(towns, currentPath[level - 1]) + first_minimum_value(towns, i)) / 2);
			}
			// Czy opłaca się sprawdzać kolejne poziomy drzewa 
			if ((currentLowerBound + currentWeight) <= pathCost)
			{
				//aktualizacja 
				currentPath[level] = i;
				visited[i] = true;
				// rekurencja dla kolejnego poziomu
				bnb_recursion(towns, currentLowerBound, currentWeight, level + 1, currentPath);
			}

			// W przeciwnym przypadku musimy cofnąć się do wezła o wyższym poziomie 
			currentWeight -= towns.neighborhoodMatrix[currentPath[level - 1]][ i];
			currentLowerBound = temp;

			// Resetowanie tablicy odwiedzanych miast
			for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
			{
				visited[i] = false;
			}
			// Ustawianie właściwych odwiedzonych 
			for (int j = 0; j <= level - 1; j++)
			{
				visited[currentPath[j]] = true;
			}
		}
	}
}

void branch_and_bound::find_path(vector_matrix towns)
{
	int* currentPath = new int[towns.nVertices + 1];
	int currentLowerBound = 0;

	// -1 oznacza, że aktualna droga jest pusta 
	for (int i = 0; i < towns.nVertices + 1; i++)
	{
		currentPath[i] = -1;
	}
	for (int i = 0; i < towns.nVertices; i++)
	{
		visited[i] = false;
	}

	for (int i = 0; i < towns.nVertices; i++)
	{
		currentLowerBound += (first_minimum_value(towns, i) + second_minimum_value(towns, i));
	}
	currentLowerBound = currentLowerBound / 2;
	
	//wierzcholek startowy
	visited[0] = true;
	currentPath[0] = 0;

	bnb_recursion(towns, currentLowerBound, 0, 1, currentPath);
}


void branch_and_bound::print_result()
{
	cout << "Sciezka: " << endl;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		cout << path[i] << " ";
	}
	cout << 0 << endl;
	cout << "wagaSciezki = " << pathCost << endl;
	cout << endl;
}

vector<int> branch_and_bound::getPath()
{
	vector<int> vec;
	vec.assign(path, path + neighborhoodMatrix.nVertices);
	vec.push_back(path[0]);
	return vec;
}

int branch_and_bound::getCost()
{
	// return pathCost;
	int result = neighborhoodMatrix.neighborhoodMatrix[path[neighborhoodMatrix.nVertices - 1]][path[0]];
	for (int i = 0; i < neighborhoodMatrix.nVertices - 1; i++)
	{
		result += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	return result;
}
