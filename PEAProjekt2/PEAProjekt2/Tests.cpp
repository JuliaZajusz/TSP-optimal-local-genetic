#include "Tests.h"
#include <sstream>
#include <cmath>
#include <ctime>
#include "BruteForce.h"
#include "VectorMatrix.h"
#include "DynamicProgramming.h"
#include "branch_and_bound.h"
#include "SimulatedAnnealing.h"
#include "SourceConverter.h"
#include "TabuSearch.h"

using namespace std;

Tests::Tests()
{
	// this->BruteForceTest();
}

Tests::~Tests()
{
}

void Tests::ZachowajCzas() {
	timeus = (float)((1000000.0 * elapsed) / frequency);
}


void Tests::zapiszStatystykeDoPliku(std::string nazwapliku, float timeus) {
	std::ofstream plik;
	plik.open(nazwapliku, std::ios_base::app);
	plik << timeus << " ";
	plik.close();
}

void Tests::zapiszDoPliku(std::string nazwapliku, std::string tresc) {
	std::ofstream plik;
	plik.open(nazwapliku, std::ios_base::app);
	plik << tresc;
	plik.close();
}

void Tests::BruteForceTest(int matrixSizes[], int tablength, string filename)
{
	for (int a = 0; a < tablength; a++) {
		matrix m;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
		for (int i = 0; i < 10; i++)
		{
			m = *new matrix(matrixSize);
			clock_t begin = clock();
			brute_force bruteForce(m);
			clock_t end = clock();
			timeSum += double(end - begin) / (CLOCKS_PER_SEC / (1000));
		}
		zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
		zapiszStatystykeDoPliku(filename, timeSum / 10);
		zapiszDoPliku(filename, "ms\n");
		zapiszStatystykeDoPliku(filename, (timeSum * 1000) / (10));
		zapiszDoPliku(filename, "us\n");
	}
}

void Tests::DynamicProgrammingTest(int matrixSizes[], int tablength, string filename)
{
	for (int a = 0; a < tablength; a++) {
		vector_matrix n;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
		for (int i = 0; i < 10; i++)
		{
			n = *new vector_matrix(matrixSize);
			clock_t begin = clock();
			dynamic_programming dynamicProgramming(n);
			clock_t end = clock();
			timeSum += double(end - begin) / (CLOCKS_PER_SEC/(1000));
		}
		zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
		zapiszStatystykeDoPliku(filename, timeSum / 10);
		zapiszDoPliku(filename, "ms\n");
		zapiszStatystykeDoPliku(filename, (timeSum * 1000) / (10));
		zapiszDoPliku(filename, "us\n");
	}
}

void Tests::BranchAndBoundTest(int matrixSizes[], int tablength, std::string filename)
{
	for (int a = 0; a < tablength; a++) {
		vector_matrix n;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
		for (int i = 0; i < 10; i++)
		{
			n = *new vector_matrix(matrixSize);
			clock_t begin = clock();
			branch_and_bound branch_and_bound(n);
			clock_t end = clock();
			timeSum += double(end - begin) / (CLOCKS_PER_SEC / (1000));
		}
		zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
		zapiszStatystykeDoPliku(filename, timeSum / 10);
		zapiszDoPliku(filename, "ms\n");
		zapiszStatystykeDoPliku(filename, (timeSum * 1000) / (10));
		zapiszDoPliku(filename, "us\n");
	}
}

void Tests::SimulatedAnnealingTest(int matrixSizes[], int tablength, std::string filename)
{
	for (int a = 0; a < tablength; a++) {
		vector_matrix n;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
		for (int i = 0; i < 10; i++)
		{
			n = *new vector_matrix(matrixSize);
			printMatrixToFile(filename, n);
			clock_t begin = clock();
			SimulatedAnnealing simulated_annealing(n);
			clock_t end = clock();
			timeSum += double(end - begin) / (CLOCKS_PER_SEC / (1000));
			vector<int> path = simulated_annealing.getPath();
			printMPathToFile(filename, path);
			zapiszDoPliku(filename, "koszt sciezki: " + to_string(simulated_annealing.calculatePathCost(path)) + "\n");
		}
		zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
		zapiszStatystykeDoPliku(filename, timeSum / 10);
		zapiszDoPliku(filename, "ms\n");
		zapiszStatystykeDoPliku(filename, (timeSum * 1000) / (10));
		zapiszDoPliku(filename, "us\n");
	}
}



void Tests::doAndSavePathAndCosts_BF(std::string filename, matrix n)
{
	// double timeSum = 0;

	// clock_t begin2 = clock();
	brute_force brute_force(n);
	// clock_t end2 = clock();
	// timeSum += double(end2 - begin2) / (CLOCKS_PER_SEC / (1000));

	zapiszDoPliku(filename, "BruteForce: ");
	printMPathToFile(filename, brute_force.getPath());
	zapiszDoPliku(filename, "koszt sciezki: " + to_string(brute_force.getCost()) + "\n");
}


void Tests::doAndSavePathAndCosts_DP(std::string filename, vector_matrix n)
{
	// double timeSum = 0;

	// clock_t begin2 = clock();
	dynamic_programming dynamicProgramming(n);
	// clock_t end2 = clock();
	// timeSum += double(end2 - begin2) / (CLOCKS_PER_SEC / (1000));

	zapiszDoPliku(filename, "DynamicProgramming: ");
	printMPathToFile(filename, dynamicProgramming.getPath());
	zapiszDoPliku(filename, "koszt sciezki: " + to_string(dynamicProgramming.getCost()) + "\n");
}

float Tests::doAndSavePathAndCosts_BnB(std::string filename, vector_matrix n)
{
	// double timeSum = 0;

	// clock_t begin1 = clock();
	branch_and_bound branch_and_bound(n);
	// clock_t end1 = clock();
	// timeSum += double(end1 - begin1) / (CLOCKS_PER_SEC / (1000));
	
	zapiszDoPliku(filename, "BranchAndBound: ");
	printMPathToFile(filename, branch_and_bound.getPath());
	zapiszDoPliku(filename, "koszt sciezki: " + to_string(branch_and_bound.getCost()) + "\n");
	return branch_and_bound.getCost();
}

int factorial(int n)
{
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

float Tests::doAndSavePathAndCosts_SA(std::string filename, vector_matrix n)
{
	// for(int i = 0; i<3; i++)
	// {
	double timeSum = 0;

	clock_t begin3 = clock();
	SimulatedAnnealing simulated_annealing(n, 20, 0.95 ,  150 * n.nVertices);
	clock_t end3 = clock();
	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));

	zapiszDoPliku(filename, "SimulatedAnnealing: ");
	printMPathToFile(filename, simulated_annealing.getPath());
	zapiszDoPliku(filename, "koszt sciezki: " + to_string(simulated_annealing.calculatePathCost(simulated_annealing.getPath())) + "\n");
	zapiszDoPliku(filename, "Iteracje: " + to_string(simulated_annealing.getIterations()) + " wspolczynnikStygniecia: " + to_string(simulated_annealing.getInitialTempCoefficient()) + " wewnetrzne iteracje: " + to_string(simulated_annealing.getInternalIterations()) + "\n");
	
	zapiszDoPliku(filename, "Czas: "  + to_string(timeSum));
	zapiszDoPliku(filename, "ms\n");
	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	zapiszDoPliku(filename, "us\n");
	// }

	return simulated_annealing.calculatePathCost(simulated_annealing.getPath());
}


float Tests::doAndSavePathAndCosts_TS(std::string filename, vector_matrix n)
{
	// for(int i = 0; i<3; i++)
	// {
	// double timeSum = 0;
	//
	// clock_t begin3 = clock();
	// TabuSearch tabu_search(n, 20, i, true,0.3, 500000* n.nVertices, true, 10, 3*n.nVertices-1);  //br17.atsp
	// TabuSearch tabu_search(n, 10, 2, true,0.0003, 500000* n.nVertices, true, 10, 3*n.nVertices-1);


	// TabuSearch tabu_search(n, 10, 2, true,0.0003, pow(100,i+1) * 5* n.nVertices, true, 10, 3*n.nVertices-1);
	// clock_t end3 = clock();
	// timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
	//
	// zapiszDoPliku(filename, "TabuSearch: ");
	// zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, true,0.0003, pow(100,i+1) * 500* n.nVertices, true, 10, 3*n.nVertices-1);");
	// printMPathToFile(filename, tabu_search.getPath());
	// zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	// zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	// zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	// zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor())+ "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
	//
	// zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	// zapiszDoPliku(filename, "ms\n");
	// zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	// zapiszDoPliku(filename, "us\n");
	// }

	// for (int i = 0; i < 3; i++)
	// {
	// 	double timeSum = 0;
	//
	// 	clock_t begin3 = clock();
	//
	// 	TabuSearch tabu_search(n, 10, 2, true, 50*i + 50, 500 * n.nVertices, false, 20, 3 * n.nVertices - 1);
	// 	// TabuSearch tabu_search(n, 10, 2, true, 0.0003, 500 * n.nVertices, false, 20, 3 * n.nVertices - 1);
	// 	clock_t end3 = clock();
	// 	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
	//
	// 	zapiszDoPliku(filename, "TabuSearch: ");
	// 	zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, true, 50*i + 50, 500 * n.nVertices, true, 20, 3 * n.nVertices - 1);");
	// 	printMPathToFile(filename, tabu_search.getPath());
	// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	// 	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	// 	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	// 	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
	//
	// 	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	// 	zapiszDoPliku(filename, "ms\n");
	// 	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	// 	zapiszDoPliku(filename, "us\n");
	// }
	//
	// for (int i = 0; i < 3; i++)
	// {
	// 	double timeSum = 0;
	//
	// 	clock_t begin3 = clock();
	// 	TabuSearch tabu_search(n, 10, 2, true, 3, 500, true, 20, (i+1) * n.nVertices - 1);
	// 	clock_t end3 = clock();
	// 	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
	//
	// 	zapiszDoPliku(filename, "TabuSearch: ");
	// 	zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, true, 3, 500, true, 20, (i+1) * n.nVertices - 1);");
	// 	printMPathToFile(filename, tabu_search.getPath());
	// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	// 	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	// 	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	// 	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
	//
	// 	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	// 	zapiszDoPliku(filename, "ms\n");
	// 	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	// 	zapiszDoPliku(filename, "us\n");
	// }

	// for (int i = 0; i < 3; i++)
	// {
	// 	double timeSum = 0;
	//
	// 	clock_t begin3 = clock();
	// 	TabuSearch tabu_search(n, i*2 + 2, 2, true, 3, 500, true, 20, n.nVertices - 1);
	// 	clock_t end3 = clock();
	// 	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
	//
	// 	zapiszDoPliku(filename, "TabuSearch: ");
	// 	zapiszDoPliku(filename, "TabuSearch tabu_search(n, i*2 + 2, 2, true, 3, 500, true, 20, n.nVertices - 1);");
	// 	printMPathToFile(filename, tabu_search.getPath());
	// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	// 	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	// 	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	// 	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
	//
	// 	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	// 	zapiszDoPliku(filename, "ms\n");
	// 	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	// 	zapiszDoPliku(filename, "us\n");
	// }

	// for (int i = 0; i < 3; i++)
	// {
	// 	double timeSum = 0;
	//
	// 	clock_t begin3 = clock();
	// 	TabuSearch tabu_search(n, 10, 2, true, 3, 50000, true, 20 * i + 10, 3 *n.nVertices - 1);
	// 	clock_t end3 = clock();
	// 	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
	//
	// 	zapiszDoPliku(filename, "TabuSearch: ");
	// 	zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, true, 3, 50000, true, 20 * i + 10, 3 *n.nVertices - 1);");
	// 	printMPathToFile(filename, tabu_search.getPath());
	// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	// 	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	// 	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	// 	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
	//
	// 	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	// 	zapiszDoPliku(filename, "ms\n");
	// 	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	// 	zapiszDoPliku(filename, "us\n");
	// }

// for (int i = 0; i < 3; i++)
// {
// 	double timeSum = 0;
//
// 	clock_t begin3 = clock();
// 	TabuSearch tabu_search(n, 10, 2, false, 3, 50000, true, 10, 3 * n.nVertices - 1);
// 	clock_t end3 = clock();
// 	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));
//
// 	zapiszDoPliku(filename, "TabuSearch: ");
// 	zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, false, 3, 50000, true, 10, 3 * n.nVertices - 1);");
// 	printMPathToFile(filename, tabu_search.getPath());
// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
// 	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
// 	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
// 	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");
//
// 	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
// 	zapiszDoPliku(filename, "ms\n");
// 	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
// 	zapiszDoPliku(filename, "us\n");
// }

// for (int i = 0; i < 3; i++)
// {
	double timeSum = 0;

	clock_t begin3 = clock();
	TabuSearch tabu_search(n, 10, 2, true, 3, 500, true, 10, 2 * n.nVertices - 1);
	clock_t end3 = clock();
	timeSum += double(end3 - begin3) / (CLOCKS_PER_SEC / (1000));

	zapiszDoPliku(filename, "TabuSearch: ");
	zapiszDoPliku(filename, "TabuSearch tabu_search(n, 10, 2, true, 3, 500, true, 10, 2 * n.nVertices - 1);");
	printMPathToFile(filename, tabu_search.getPath());
	zapiszDoPliku(filename, "koszt sciezki: " + to_string(tabu_search.calculatePathCost(tabu_search.getPath())) + "\n");
	zapiszDoPliku(filename, "Czas: " + to_string(tabu_search.getTimer()) + " metoda sasiedztwa: " + tabu_search.getNeighbourMethod() + "kadencje: " + to_string(tabu_search.getCadence()) + "dywersyfikacja: " + to_string(tabu_search.getDiversification()) + "\n");
	zapiszDoPliku(filename, "Iteracje: " + to_string(tabu_search.getIterations()) + " alfa: " + to_string(tabu_search.getAlfa()) + "\n");
	zapiszDoPliku(filename, "Wspolczynnik dywersyfikacji: " + to_string(tabu_search.getDiversificationFactor()) + "Pierwsza sciezka zachlannie?: " + to_string(tabu_search.getGreedy()) + "\n");

	zapiszDoPliku(filename, "Czas: " + to_string(timeSum));
	zapiszDoPliku(filename, "ms\n");
	zapiszStatystykeDoPliku(filename, (timeSum * 1000));
	zapiszDoPliku(filename, "us\n");
// }

	// return tabu_search.calculatePathCost(tabu_search.getPath());
	return -100;
}


void Tests::doAndSavePathsAndCosts(std::string filename, vector_matrix n, int i)
{
	// matrix m = *new matrix(n);
	// doAndSavePathAndCosts_BF(filename, n);
	// float bnbCost = doAndSavePathAndCosts_BnB(filename, n);
	// doAndSavePathAndCosts_DP(filename, n);
	// float saCost = doAndSavePathAndCosts_SA(filename, n);
	float tsCost = doAndSavePathAndCosts_TS(filename, n);
	// cout << bnbCost << " " << saCost << endl;
	// saveToDifferenceTable(n.nVertices, bnbCost, tsCost, i);
}

void Tests::testFromFiles(vector<string> fielpaths, std::string resultFilename)
{
	SourceConverter c;
	vector_matrix n;
	for (int i = 0; i < fielpaths.size(); i++)
	{
		c.loadDataFromFile(fielpaths[i]);
		zapiszDoPliku(resultFilename, "**************************************************************************************\n");
		zapiszDoPliku(resultFilename, c.getInstanceName());
		zapiszDoPliku(resultFilename, "\n**************************************************************************************\n");
		n = c.getVectorMatrixATSP();
		zapiszDoPliku(resultFilename, "rozmiar macierzy: " + to_string(n.nVertices) + "\n");
		// n.printNeighborhoodMatrix();
		doAndSavePathsAndCosts(resultFilename, n, i);
		zapiszDoPliku(resultFilename, "\n\n");
	}
}

void Tests::TestFromRandomMatrix(int matrixSizes[], int tablength, std::string filename)
{
	for (int a = 0; a < tablength; a++) {
		vector_matrix n;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
		n = *new vector_matrix(matrixSize);
		zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
		printMatrixToFile(filename, n);

		matrix m = *new matrix(n);

		doAndSavePathsAndCosts(filename, n, a);
		zapiszDoPliku(filename, "\n\n");

		// 	// clock_t begin = clock();
		// 	brute_force bruteForce(m);
		//
		// 	zapiszDoPliku(filename, "BruteForce: ");
		// 	printMPathToFile(filename, bruteForce.getPath());
		// 	zapiszDoPliku(filename, "koszt sciezki: " + to_string(bruteForce.getCost()) + "\n");
		//
		// 	doAndSavePathsAndCosts(filename, n);
		//
		// // zapiszStatystykeDoPliku(filename, timeSum);
		// // zapiszDoPliku(filename, "ms\n");
		// // zapiszStatystykeDoPliku(filename, (timeSum * 1000));
		// // zapiszDoPliku(filename, "us\n");
	}
	zapiszDoPlikuDifferenceTable(filename);
}

void Tests::saveToDifferenceTable(int nVertices, float result1, float result2, int i)
{
	differenceTable[0][i]=(nVertices);
	differenceTable[1][i]=(result2 - result1);
	differenceTable[2][i]=((result2 - result1) / result1 * 100);
}

void Tests::zapiszDoPlikuDifferenceTable(std::string nazwapliku)
{
	std::ofstream plik;
	plik.open(nazwapliku, std::ios_base::app);
	plik << "Roznice: \n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 26; j++) {
			plik << differenceTable[i][j] << " & ";
		}
		plik << " \\"<< std::endl;
	}
	plik.close();
}


void Tests::printMatrixToFile(std::string nazwapliku, vector_matrix m)
{
	std::ofstream plik;
	plik.open(nazwapliku, std::ios_base::app);
	plik << std::endl;

	for (int i = 0; i < m.nVertices; i++) {
		for (int j = 0; j < m.nVertices; j++) {
			plik << m.neighborhoodMatrix[i][j] << " ";
		}
		plik << std::endl;
	}
	plik.close();
}

void Tests::printMPathToFile(std::string nazwapliku, vector<int> path)
{
	std::ofstream plik;
	plik.open(nazwapliku, std::ios_base::app);
	plik << "Sciezka: ";
		for (int j = 0; j < path.size(); j++) {
			plik << path[j] << " ";
		}
		plik << std::endl;
	plik.close();
}
