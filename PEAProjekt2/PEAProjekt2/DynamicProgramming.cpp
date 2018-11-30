#include "DynamicProgramming.h"
#include "matrix.h"

dynamic_programming::dynamic_programming(vector_matrix m) {
	neighborhoodMatrix = m;
	nSet = static_cast<int>(pow(2, m.nVertices));
	subcostsMatrix = vector<vector<int>>(nSet, vector<int>(m.nVertices, MAXINT));
	find_path();
}

void dynamic_programming::find_path() {
	build_subsets(subcostsMatrix, neighborhoodMatrix.neighborhoodMatrix);
	path = min_path(subcostsMatrix, neighborhoodMatrix.neighborhoodMatrix);
}

void dynamic_programming::build_subsets(vector<vector<int>> & subcostsMatrix, const vector<vector<int>> & costsMatrix)
{
	// Start with shortest possible tour (starting and ending at the first city)
	subcostsMatrix[1][0] = 0;

	// Iterate all subsets that include the first city, with size greater than 2
	for (size_t s = 3; s < nSet; s += 2) {
		// Iterate ending cities (excluding first city)
		for (int j = 1; j < neighborhoodMatrix.nVertices; j++) {
			//jeśli bitowy iloczyn s i 2^j jest równy 0
			if (!(s & (1 << j)))  //it is actually multiplying 1 by 2^j;       << bit shift operation (i.e. 1 << 1 means: 00000000 00000001 changes to 00000000 00000010)
			{
				continue;
			}
				

			// Exclude ending city j from subset: S - {j}
			size_t t = s & ~(1 << j);

			// Find minimum sub-distance for this subtour with j as ending city
			for (int i = 0; i < neighborhoodMatrix.nVertices; i++) {
				if (s & (1 << i) && i != j && subcostsMatrix[t][i] < MAXINT)
					subcostsMatrix[s][j] = min(subcostsMatrix[s][j], subcostsMatrix[t][i] + costsMatrix[i][j]);
			}
		}
	}
}

list<int> dynamic_programming::min_path(vector<vector<int>> & subcostsMatrix, const vector<vector<int>> & costsMatrix)
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

void dynamic_programming::print_result() {
	cout << "Sciezka: " << endl;
	for (list<int>::reverse_iterator it = path.rbegin(); it != path.rend(); ++it) {
		cout << *it << " ";
		if (it != path.rbegin()) {
			pathCost += neighborhoodMatrix.neighborhoodMatrix[*prev(it)][*it];
		}
	}
	cout << endl << "wagaSciezki = " << pathCost << endl;
	cout << endl;
}

vector<int> dynamic_programming::getPath()
{
	vector<int> vec(path.begin(), path.end());
	return vec;
}

int dynamic_programming::getCost()
{
	int cost=0;
	for (list<int>::reverse_iterator it = path.rbegin(); it != path.rend(); ++it) {
		if (it != path.rbegin()) {
			cost += neighborhoodMatrix.neighborhoodMatrix[*prev(it)][*it];
		}
	}
	return cost;
}
