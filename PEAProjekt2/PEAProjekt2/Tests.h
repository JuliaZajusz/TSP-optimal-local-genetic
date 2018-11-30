#pragma once

#include<conio.h>
#include<string>
#include<iostream>
#include <iomanip>
#include <fstream>
#include "VectorMatrix.h"

class Tests {
public:
	long long int frequency, start, elapsed;
	float times;
	float timems;
	float timeus;

public:
	Tests();
	~Tests();
	void ZachowajCzas();
	void zapiszStatystykeDoPliku(std::string nazwapliku, float timeus);
	void zapiszDoPliku(std::string nazwapliku, std::string tresc);
	void BruteForceTest(int matrixSizes[], int tablength, std::string filename);
	void DynamicProgrammingTest(int matrixSizes[], int tablength, std::string filename);
	void BranchAndBoundTest(int matrixSizes[], int tablength, std::string filename);
	void SimulatedAnnealingTest(int matrixSizes[], int tablength, std::string filename);
	void printMatrixToFile(std::string nazwapliku, vector_matrix m);
	void printMPathToFile(std::string nazwapliku, vector<int> path);
	void CompareBnBDPTest(int matrixSizes[], int tablength, std::string filename);
};
