#include "VectorMatrix.h"
#include "matrix.h"

vector_matrix::vector_matrix()
{
}

vector_matrix::vector_matrix(int vertices)
{
	neighborhoodMatrix = vector<vector<int>>(vertices, vector<int>(vertices, PLACEHOLDER_VALUE));
	nVertices = vertices;

	for (int i = 0; i < vertices; i++) {
		for (int j = 0; j < vertices; j++) {
			int x;
			if (i == j)
			{
				x = 0;
			}
			else
			{
				x = rand() % 100;
			}
			neighborhoodMatrix[i][j] = x;
		}
	}
}

vector_matrix::~vector_matrix()
{
}

bool vector_matrix::loadFromFile(std::string filename)
{
	std::fstream file;
	file.open(filename.c_str());
	if (!file.good()) {
		cout << "Nazwa pliku jest nieprawidlowa.\n";
		return false;
	}
	int matrixSize;
	file >> matrixSize;
	cout << matrixSize << endl;
	nVertices = matrixSize;
	neighborhoodMatrix = vector<vector<int>>(nVertices, vector<int>(nVertices, PLACEHOLDER_VALUE));
	while (true) {
		if (file.good()) {
			for (int i = 0; i < matrixSize; i++) {
				for (int j = 0; j < matrixSize; j++) {
					int x;
					file >> x;
					neighborhoodMatrix[i][j] = x;
				}
			}
		}
		else {
			break;
		}
	}
	file.close();
	return true;
}

void vector_matrix::printNeighborhoodMatrix()
{
	for (int i = 0; i < nVertices; i++) {
		for (int j = 0; j < nVertices; j++) {
			std::cout << neighborhoodMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
