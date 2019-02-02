#pragma once

#include<conio.h>
#include<string>
#include<iostream>
#include <iomanip>
#include <fstream>
#include "VectorMatrix.h"

class matrix;

class Tests {
public:
	long long int frequency, start, elapsed;
	float times;
	float timems;
	float timeus;
	std::vector<vector<int>> differenceTable = std::vector<vector<int>>(3, vector<int>(26, -1));
public:
	Tests();
	~Tests();
	int factorial(int n);
	void ZachowajCzas();
	void zapiszStatystykeDoPliku(std::string nazwapliku, float timeus);
	void zapiszDoPliku(std::string nazwapliku, std::string tresc);
	void BruteForceTest(int matrixSizes[], int tablength, std::string filename);
	void DynamicProgrammingTest(int matrixSizes[], int tablength, std::string filename);
	void BranchAndBoundTest(int matrixSizes[], int tablength, std::string filename);
	void doAndSavePathsAndCosts(std::string filename, vector_matrix n, int i);
	void SimulatedAnnealingTest(int matrixSizes[], int tablength, std::string filename);
	void printMatrixToFile(std::string nazwapliku, vector_matrix m);
	void printMPathToFile(std::string nazwapliku, vector<int> path);
	void doAndSavePathAndCosts_BF(std::string filename, matrix n);
	void doAndSavePathAndCosts_DP(std::string filename, vector_matrix n);
	float doAndSavePathAndCosts_BnB(std::string filename, vector_matrix n);
	float doAndSavePathAndCosts_SA(std::string filename, vector_matrix n);
	float doAndSavePathAndCosts_TS(std::string filename, vector_matrix n);
	float doAndSavePathAndCosts_GA(std::string filename, vector_matrix n);
	float doAndSavePathAndCosts_ISLGA(std::string filename, vector_matrix n);
	void testFromFiles(vector<string> fielpaths, std::string resultFilename);
	void TestFromRandomMatrix(int matrixSizes[], int tablength, std::string filename);
	void saveToDifferenceTable(int nVertices, float result1, float result2, int i);
	void zapiszDoPlikuDifferenceTable(std::string filename);
};
