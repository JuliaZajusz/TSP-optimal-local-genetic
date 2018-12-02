#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include "VectorMatrix.h"
#define M_PI 3.14159265358979323846

#define INF 9999999
class SourceConverter
{
private:
	char problem;
	std::string instanceName;
	int dimension;
	int ** tabATSP;
	double ** tabTSP;

	std::string fileType;

public:
	SourceConverter();
	~SourceConverter();
	bool loadDataFromFile(std::string filename);
	void PrintMatrix();
	int GetDimension();
	char GetProblem();
	int ** GetATSPtab();
	double ** GetTSPtab();
	int GetATSPTabByIJ(int i, int j);
	vector_matrix getVectorMatrixATSP();
	std::string getInstanceName();
};