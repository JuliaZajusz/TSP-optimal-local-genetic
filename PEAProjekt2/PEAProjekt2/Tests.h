#pragma once

#include<conio.h>
#include<string>
#include<iostream>
#include <iomanip>
#include <fstream>

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
};
