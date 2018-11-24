#include "pch.h"
#include "BruteForce.h"
#include <iostream>

using namespace std;

brute_force::brute_force(matrix m)
{
	neighborhoodMatrix = m;
	path = new int[m.nVertices];             // Tworzymy struktury dynamiczne i inicjujemy je
	find_path();
}

bool permutation(int *begin, int *end)
{
	if (begin == end) return false;
	int *i = begin;
	++i;
	if (i == end) return false;
	i = end;
	--i;

	while (true) {
		int *j = i;
		--i;

		if (*i < *j) {
			int *k = end;
			while (!(*i < *--k))
				/* pass */;
			iter_swap(i, k);
			reverse(j, end);
			return true;
		}

		if (i == begin) {
			reverse(begin, end);
			return false;
		}
	}
}

void brute_force::find_path() {
	int *verticles=new int[neighborhoodMatrix.nVertices];
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++){
		verticles[i] = i;
	}

	do {
		if(check_path_consistency(verticles))
		{
			int cost = calculate_costs(verticles);
			if (cost< pathCost)
			{
				pathCost = cost;
				for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
				{
					path[i] = verticles[i];
				}
			}
		}
	} while (permutation(verticles, verticles + neighborhoodMatrix.nVertices));
}

bool brute_force::check_path_consistency(int* verticles)
{
	if (neighborhoodMatrix.neighborhoodMatrix[verticles[neighborhoodMatrix.nVertices-1]][verticles[0]] == -1)
	{
		return false;
	}
	for(int i =0;i<neighborhoodMatrix.nVertices-1;i++)
	{
		if(neighborhoodMatrix.neighborhoodMatrix[verticles[i]][verticles[i+1]]==-1)
		{
			return false;
		}
	}
	return true;
}

int brute_force::calculate_costs(int* verticles) {
	int result = neighborhoodMatrix.neighborhoodMatrix[verticles[neighborhoodMatrix.nVertices - 1]][verticles[0]];
	for (int i = 0; i < neighborhoodMatrix.nVertices - 1; i++)
	{
		result += neighborhoodMatrix.neighborhoodMatrix[verticles[i]][verticles[i + 1]];
	}
	return result;
}


void brute_force::print_result()
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