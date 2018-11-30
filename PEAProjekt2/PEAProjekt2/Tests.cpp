#include "Tests.h"
#include <sstream>
#include <cmath>
#include <ctime>
#include "BruteForce.h"
#include "VectorMatrix.h"
#include "DynamicProgramming.h"
#include "branch_and_bound.h"
#include "SimulatedAnnealing.h"

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

void Tests::CompareBnBDPTest(int matrixSizes[], int tablength, std::string filename)
{
	for (int a = 0; a < tablength; a++) {
		vector_matrix n;
		double timeSum = 0;
		int matrixSize = matrixSizes[a];
			n = *new vector_matrix(matrixSize);
			zapiszDoPliku(filename, "rozmiar macierzy: " + to_string(matrixSize) + "\n");
			printMatrixToFile(filename, n);

			matrix m = *new matrix(n);
			// clock_t begin = clock();
			brute_force bruteForce(m);

			// clock_t begin1 = clock();
			branch_and_bound branch_and_bound(n);
			// clock_t end1 = clock();
			// timeSum += double(end1 - begin1) / (CLOCKS_PER_SEC / (1000));

			// clock_t begin2 = clock();
			dynamic_programming dynamicProgramming(n);
			// clock_t end2 = clock();
			// timeSum += double(end2 - begin2) / (CLOCKS_PER_SEC / (1000));

					// clock_t begin2 = clock();
			SimulatedAnnealing simulated_annealing(n);
			// clock_t end2 = clock();
			// timeSum += double(end2 - begin2) / (CLOCKS_PER_SEC / (1000));

			zapiszDoPliku(filename, "BruteForce: ");
			printMPathToFile(filename, bruteForce.getPath());
			zapiszDoPliku(filename, "koszt sciezki: " + to_string(bruteForce.getCost()) + "\n");
		zapiszDoPliku(filename, "BranchAndBound: ");
		printMPathToFile(filename, branch_and_bound.getPath());
		zapiszDoPliku(filename, "koszt sciezki: " + to_string(branch_and_bound.getCost()) + "\n");
		zapiszDoPliku(filename, "DynamicProgramming: ");
		printMPathToFile(filename, dynamicProgramming.getPath());
		zapiszDoPliku(filename, "koszt sciezki: " + to_string(dynamicProgramming.getCost()) + "\n");
		zapiszDoPliku(filename, "SimulatedAnnealing: ");
		printMPathToFile(filename, simulated_annealing.getPath());
		zapiszDoPliku(filename, "koszt sciezki: " + to_string(simulated_annealing.calculatePathCost(simulated_annealing.getPath())) + "\n");
		zapiszDoPliku(filename, "\n\n");

		// zapiszStatystykeDoPliku(filename, timeSum);
		// zapiszDoPliku(filename, "ms\n");
		// zapiszStatystykeDoPliku(filename, (timeSum * 1000));
		// zapiszDoPliku(filename, "us\n");
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
