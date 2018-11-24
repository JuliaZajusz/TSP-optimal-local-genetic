#include "SimulatedAnnealing.h"
#include <algorithm>


SimulatedAnnealing::SimulatedAnnealing()
{
}

SimulatedAnnealing::SimulatedAnnealing(vector_matrix m)
{
	neighborhoodMatrix = m;
	// path = new int[neighborhoodMatrix.nVertices + 1];
	// visited = new bool[neighborhoodMatrix.nVertices];
	find_path(m, 20, 0.9);
}

void SimulatedAnnealing::save_path(int* currentPath)
{
}

// vector<int> SimulatedAnnealing::getRandomNeigboringSolution(vector<int> path)
// {
// 	int indexOfFirstSwappedVerticle = std::rand() % path.size();
// 	int indexOfSecondSwappedVerticle = std::rand() % path.size();
// 	while(indexOfFirstSwappedVerticle == indexOfSecondSwappedVerticle)
// 	{
// 		indexOfSecondSwappedVerticle = std::rand() % path.size();
// 	}
// 	int swapBuffor = path[indexOfFirstSwappedVerticle];
// 	path[indexOfFirstSwappedVerticle] = path[indexOfSecondSwappedVerticle];
// 	path[indexOfSecondSwappedVerticle] = swapBuffor;
// 	return path;
// }

vector<int> SimulatedAnnealing::getRandomNeigboringSolution(vector<int> path)
{
	vector<int> neighboringPath;
	// // int indexOfFirstSwappedVerticle = std::rand() % (path.size()-1);
	// int indexOfFirstSwappedVerticle = std::rand() % path.size();
	// // int indexOfSecondSwappedVerticle = (indexOfFirstSwappedVerticle + path.size() / 2) % (path.size()-1);
	// int indexOfSecondSwappedVerticle = (indexOfFirstSwappedVerticle + path.size() / 2) % path.size();

	int indexOfFirstSwappedVerticle = std::rand() % path.size();
	int indexOfSecondSwappedVerticle = std::rand() % path.size();
	while(indexOfFirstSwappedVerticle == indexOfSecondSwappedVerticle)
	{
		indexOfSecondSwappedVerticle = std::rand() % path.size();
	}


	// cout << "index pierwszy: " << indexOfFirstSwappedVerticle << ", index drugi: " << indexOfSecondSwappedVerticle << endl;

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
				// neighboringPath.push_back(path[(indexOfSecondSwappedVerticle +indexOfFirstSwappedVerticle - i + 1) % path.size()]);
				neighboringPath.push_back(path[(indexOfFirstSwappedVerticle + 1 - (i - indexOfSecondSwappedVerticle) + path.size()) % path.size()]);
			}
		}
	}

	// cout << "path:" << endl;
	// for (int x : path)
	// cout << x << " ";
	// cout << endl;
	// cout << "firstIndex: " << indexOfFirstSwappedVerticle << ", second index: " << indexOfSecondSwappedVerticle << endl;
	// cout << "neighboringPath:" << endl;
	// for (int x : neighboringPath)
	// 	cout << x << " ";
	// cout << endl;

	return neighboringPath;
}




int SimulatedAnnealing::calculatePathCost(vector<int> path)
{
	int cost = 0;
	// cout << endl;
	for(int i = 0; i < path.size()-1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
		// cout<< neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]]<< "+";
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size()-1]][path[0]];
	// cout<< neighborhoodMatrix.neighborhoodMatrix[path[path.size()-1]][path[0]]<<endl;
	return cost;
}





void SimulatedAnnealing::find_path(vector_matrix m, int iterations, float tempCoefficient)
{
	int licznikZmianSciezki = 0;
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
	
	// sPath.push_back(sPath[0]);
	// for (int x : sPath)
	// 	cout << x << " ";
	// cout<<endl;
	
	// for (int x : sPath)  //wypisz nowa sciezke
	// 	cout << x << " ";
	// cout << endl;
	// cout << "waga Sciezki: " << calculatePathCost(sPath);
	// cout << endl;
	
	int warunek = 0;
	while (warunek<100)
	{
		for (int i = 0; i < 1*iterations; i++)
		{
			vector<int> s1Path = getRandomNeigboringSolution(sPath);  //wygenerowanie sasiedniego rozwiazania
	
	
			int sCost = calculatePathCost(sPath);
			int s1Cost = calculatePathCost(s1Path);
			int sBCost = calculatePathCost(path); //sB cost
	
	
	
			// for (int x : s1Path)  //wypisz nowa sciezke
			// 	cout << x << " ";
			// cout << endl;
			// cout << "waga Sciezki: " << s1Cost;
			// if (s1Cost <= 256) {
			// 	cout << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
			// }
			// cout << endl<< endl;
	
	
	
			if(s1Cost<sBCost)  //sB
			{
				path = s1Path;
			}
	
			int costDifference = s1Cost - sCost;
			if (costDifference < 0)
			{
				// cout << "poprawa "<<i << endl;
				sPath = s1Path;
			}
			else
			{
				double rand = (1.0 + std::rand() % (99)) / 100;

				// cout << endl << "sCost: " << sCost << " s1Cost: " << s1Cost << " " << costDifference << " " << kb * temperature;
				// cout<< " rand: " << rand << " eksponenta: " << exp(0.0 -costDifference / temperature) << endl;
				

				if (rand < exp((0.0-costDifference) / temperature))
				{
					// cout << endl << "zamiana sciezek<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
					sPath = s1Path;
					licznikZmianSciezki++;
				}
			}
		}
		temperature = tempCoefficient * temperature;
		warunek++;
	}

	cout << "Zmian sciezki nastąpiło: " << licznikZmianSciezki<<endl;
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
