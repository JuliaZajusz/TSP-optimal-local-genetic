#include "Tests.h"
#include <sstream>
#include <cmath>
#include <ctime>
#include "BruteForce.h"
#include "VectorMatrix.h"
#include "DynamicProgramming.h"
#include "branch_and_bound.h"

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
