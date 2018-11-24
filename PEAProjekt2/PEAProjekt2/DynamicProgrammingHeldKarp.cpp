#include "DynamicProgrammingHeldKarp.h"
#include <algorithm>
#include "matrix.h"

DynamicProgrammingHeldKarp::DynamicProgrammingHeldKarp(vector_matrix m) {
	neighborhoodMatrix = m;
	nSet = static_cast<int>(pow(2, m.nVertices));
	subcostsMatrix = vector<vector<int>>(nSet, vector<int>(m.nVertices, MAXINT));
	vertexMinCostDestinationMatrix = vector<vector<int>>(3, vector<int>(m.nVertices, MAXINT)); //1-cost, 2-destinationVertex, 3-etap wierzcholka (etapy liczone od końca)
	find_path();
	// print_result();
}

void DynamicProgrammingHeldKarp::find_path() {
	build_subsets(subcostsMatrix, neighborhoodMatrix.neighborhoodMatrix);
	// path = min_path(subcostsMatrix, neighborhoodMatrix.neighborhoodMatrix);
}

void DynamicProgrammingHeldKarp::build_subsets(vector<vector<int>> & subcostsMatrix, const vector<vector<int>> & costsMatrix)
{
	// vector<vector<int>> etapy = vector<vector<int>>(neighborhoodMatrix.nVertices, vector<int>(neighborhoodMatrix.nVertices, MAXINT));
	for(int i=0; i<neighborhoodMatrix.nVertices; i++)
	{
		if(neighborhoodMatrix.neighborhoodMatrix[i][0]>0)
		{
			vertexMinCostDestinationMatrix[0][i] = neighborhoodMatrix.neighborhoodMatrix[i][0];
			vertexMinCostDestinationMatrix[1][i] = 0; //koniec w wierzcholku 0
			vertexMinCostDestinationMatrix[2][i] = 0; //etap ostatni
		}
	}
	int etap = -1;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		if (vertexMinCostDestinationMatrix[2][i] > etap && vertexMinCostDestinationMatrix[2][i] != MAXINT)
			etap = vertexMinCostDestinationMatrix[2][i]; //określamy jaki był poprzedni etap //to można zrobić może rekurencyjnie przez argument
	}

	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)  //dla wszystkich wierzchołków w tabeli vertexMinCostDestinationMatrix
	{
		if (vertexMinCostDestinationMatrix[2][i] == etap) {  //jeśli wierzchołek należy do poprzedniego etapu
			for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
			{
				if (neighborhoodMatrix.neighborhoodMatrix[j][i] > 0) //sprawdź jakie wierzchołki się do niego łączą
				{
					vertexMinCostDestinationMatrix[2][j] = etap + 1; // ustaw im etap
				}
			}
		}
	}


	for (int i = 0; i < 3; i++)
	{

		for (int  j= 0; j < neighborhoodMatrix.nVertices; j++)
		{
			cout << vertexMinCostDestinationMatrix[i][j] << " ";
		}
		cout << endl;
	}


}

list<int> DynamicProgrammingHeldKarp::min_path(vector<vector<int>> & subcostsMatrix, const vector<vector<int>> & costsMatrix)
{
	list<int> path(1, 0);
	vector<bool> visited(neighborhoodMatrix.nVertices, false);

	// Backtracking start with subset that contains all cities
	size_t s = nSet - 1;

	// Mark first city as visited
	visited[0] = true;

	for (int i = 0; i < neighborhoodMatrix.nVertices - 1; i++) {

		int best_j;
		double min_dist = MAXINT;

		// Find next non-visited city with best sub-distance from
		// previous city in the path
		for (int j = 0; j < neighborhoodMatrix.nVertices; j++) {
			if (!visited[j] && subcostsMatrix[s][j] + costsMatrix[path.back()][j] < min_dist) {
				min_dist = subcostsMatrix[s][j] + costsMatrix[path.back()][j];
				best_j = j;
			}
		}

		// Mark city as visited and exclude it from the subset
		path.push_back(best_j);
		visited[best_j] = true;
		s &= ~(1 << best_j);
	}
	path.push_back(0);
	return path;
}

void DynamicProgrammingHeldKarp::print_result() {
	list<int>::const_iterator it;

	for (it = path.begin(); it != path.end(); ++it) {
		cout << *it << " ";
		if (it != path.begin()) {
			pathCost += neighborhoodMatrix.neighborhoodMatrix[*it][*prev(it)];
		}
	}
	cout << endl << pathCost << endl;
}
