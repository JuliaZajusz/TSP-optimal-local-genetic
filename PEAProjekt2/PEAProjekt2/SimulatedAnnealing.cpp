#include "SimulatedAnnealing.h"
#include <algorithm>


SimulatedAnnealing::SimulatedAnnealing()
{
}

SimulatedAnnealing::SimulatedAnnealing(vector_matrix m)
{
	neighborhoodMatrix = m;
	find_path(m, 20, 0.9);
}

vector<int> SimulatedAnnealing::getRandomNeigboringSolution(vector<int> path)
{
	vector<int> neighboringPath;
	int indexOfFirstSwappedVerticle = std::rand() % path.size();
	int indexOfSecondSwappedVerticle = std::rand() % path.size();
	while(indexOfFirstSwappedVerticle == indexOfSecondSwappedVerticle)
	{
		indexOfSecondSwappedVerticle = std::rand() % path.size();
	}

	for (int i = 0; i < path.size(); i++)
	{
		if (indexOfFirstSwappedVerticle < indexOfSecondSwappedVerticle)
		{
			//jesli wierzcholek pomiędzy swapowanymi wierzchołkami to odwroc kolejnosc
			if (i > indexOfFirstSwappedVerticle && i <= indexOfSecondSwappedVerticle)
			{
				neighboringPath.push_back(path[indexOfSecondSwappedVerticle - i + indexOfFirstSwappedVerticle + 1]);
			}
			else // w pozostałych przypadkach przepisz
			{
				neighboringPath.push_back(path[i]);
			}
		}
		else //jeśli wierzchołki zamienione kolejnością
		{
			if (i > indexOfSecondSwappedVerticle && i <= indexOfFirstSwappedVerticle)
			{
				neighboringPath.push_back(path[i]);
			}
			else
			{
				neighboringPath.push_back(path[(indexOfFirstSwappedVerticle + 1 - (i - indexOfSecondSwappedVerticle) + path.size()) % path.size()]);
			}
		}
	}

	return neighboringPath;
}




int SimulatedAnnealing::calculatePathCost(vector<int> path)
{
	int cost = 0;
	// cout << endl;
	for(int i = 0; i < path.size()-1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size()-1]][path[0]];
	return cost;
}




void SimulatedAnnealing::find_path(vector_matrix m, int iterations, float tempCoefficient)
{
	//wyznaczenie losowego rozwiązania początkowego
	vector<int> sPath;
		for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
			sPath.push_back(i);
	std::random_shuffle(sPath.begin(), sPath.end());
	double temperature = tempCoefficient * calculatePathCost(sPath);

	for (int x : sPath)
		cout << x << " ";
	cout<<endl;

	path = sPath;//sB
	
	int warunek = 0;
	while (warunek<100)
	{
		for (int i = 0; i < iterations; i++)
		{
			vector<int> s1Path = getRandomNeigboringSolution(sPath);  //wygenerowanie sasiedniego rozwiazania
	
			int sCost = calculatePathCost(sPath);
			int s1Cost = calculatePathCost(s1Path);
			int sBCost = calculatePathCost(path); //sB cost
	
			if(s1Cost<sBCost)  //sB
			{
				path = s1Path;
			}
	
			int costDifference = s1Cost - sCost;
			if (costDifference < 0)
			{
				sPath = s1Path;
			}
			else
			{
				double rand = (1.0 + std::rand() % (99)) / 100;			

				if (rand < exp((0.0-costDifference) / temperature))
				{
					sPath = s1Path;
				}
			}
		}
		temperature = tempCoefficient * temperature;
		warunek++;
	}
}

void SimulatedAnnealing::print_result()
{
	cout << "Sciezka: " << endl;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		cout << path[i] << " ";
	}
	cout << path[0] << endl;
	cout << "wagaSciezki = " << calculatePathCost(path) << endl;
	cout << endl;
}
