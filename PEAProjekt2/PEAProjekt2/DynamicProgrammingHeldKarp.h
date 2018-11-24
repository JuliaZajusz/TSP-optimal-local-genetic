#pragma once
#include <list>
#include <vector>
#include "VectorMatrix.h"
using namespace std;

class DynamicProgrammingHeldKarp
{
private:
	std::list<int> path;  //sciezka
	int pathCost = 0;  //wagaSciezki
	int nSet;
	vector_matrix neighborhoodMatrix;
	vector<vector<int>> subcostsMatrix;
	vector<vector<int>> vertexMinCostDestinationMatrix;
public:
	explicit DynamicProgrammingHeldKarp(vector_matrix m);
	void build_subsets(vector<vector<int>> &subdist, const vector<vector<int>> &dist); // Generates the minimum subdistance for each ending city in each possible subset
	list<int> min_path(vector<vector<int>> &subdist, const vector<vector<int>> &dist);
	void find_path();
	void print_result();
};
