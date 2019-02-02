#include "SimulatedAnnealing.h"
#include <algorithm>

/* uruchomienie pomiaru czasu */
void SimulatedAnnealing::startCounter() {
	counterStart = chrono::steady_clock::now();
}

/* zwraca czas pomiaru podany w ms */
double SimulatedAnnealing::getCounter() {
	auto end = chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end - counterStart).count() * 1000;
}

SimulatedAnnealing::SimulatedAnnealing()
{
}

SimulatedAnnealing::SimulatedAnnealing(vector_matrix m)
{
	neighborhoodMatrix = m;
	iterations = 10000000;
	initialTempCoefficient = 0.999999;
	warunekZatrzymania = 10000;
	find_path(neighborhoodMatrix, iterations, initialTempCoefficient);
}

SimulatedAnnealing::SimulatedAnnealing(vector_matrix m, int iter, float tempC, int intIter)
{
	neighborhoodMatrix = m;
	iterations = iter;
	initialTempCoefficient = tempC;
	warunekZatrzymania = intIter;
	find_path(neighborhoodMatrix, iterations, initialTempCoefficient);
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
	for(int i = 0; i < path.size()-1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size()-1]][path[0]];
	return cost;
}


vector<int> SimulatedAnnealing::getRandomGreedyPath(int v)
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


void SimulatedAnnealing::find_path(vector_matrix m, int iterations, float tempCoefficient)
{
	//wyznaczenie losowego rozwiązania początkowego
	vector<int> sPath = getRandomGreedyPath(rand()% (neighborhoodMatrix.nVertices -1));
	// 	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	// 		sPath.push_back(i);
	// std::random_shuffle(sPath.begin(), sPath.end());
	// double temperature = tempCoefficient * calculatePathCost(sPath);
	double temperature = 100* calculatePathCost(sPath);

	path = sPath;//sB
	startCounter();
	int warunek = 0;
	// while (warunek< warunekZatrzymania)
	// {
		for (int i = 0; i < iterations; i++)
		{
			// int counter = getCounter();
			// if(counter % 1000==0)
			// {
			// 	cout << calculatePathCost(path) << endl;
			// }
			if (getCounter() > 10000)
			{
				cout << "Koniec czasu";
				return;
			}
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
				warunek = 0;
			}
			else
			{
				double rand = (1.0 + std::rand() % (99)) / 100;			

				if (rand < exp((0.0-costDifference) / temperature))
				{
					sPath = s1Path;
				}
				else
				{
					warunek++;
				}
			}
			if(warunek> warunekZatrzymania)
			{
				break;
			}
		}
		temperature = tempCoefficient * temperature;
		// cout << warunek<<" ";
	}
// }

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

vector<int> SimulatedAnnealing::getPath()
{
	return path;
}

int SimulatedAnnealing::getIterations()
{
	return iterations;
}

int SimulatedAnnealing::getInternalIterations()
{
	return warunekZatrzymania;
}

float SimulatedAnnealing::getInitialTempCoefficient()
{
	return initialTempCoefficient;
}
