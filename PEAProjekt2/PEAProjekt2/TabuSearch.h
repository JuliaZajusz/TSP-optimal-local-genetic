#pragma once

#include "VectorMatrix.h"
#include "matrix.h"
#include <chrono>
#include "City.h"

class TabuSearch {
	vector_matrix neighborhoodMatrix;
	vector<int> path;
	int pathCost = MAXINT;
	// int iterations;
	// float initialTempCoefficient;
	// int warunekZatrzymania;
	std::chrono::steady_clock::time_point counterStart;
	int timer;
	int f1, f2, d1, d2;
	int neighbourhoodMode; //typ sąsiedztwa 2 - SWAP, 1 - INWERT, 0 - INSERT
	bool diversification;       // włączenie/wyłączenie dywersyfikacji
	int cadence;
	City * tabulist;                 // listy tabu (lista zakazanych przejść pomiędzy miastami)
	int iteration;					 // liczba iteracji pętli głównej
	int alfa;					// Współczynnik alfa. Im większy tym mniejsze prawpodobonieństwo wysątpienia kryterium aspiracji
	double diversificationFactor;
	bool greedy;
	vector<int> current_path;               // ścieżka lokalna (istenieje wewnątrz pętli E1)
	vector<int> main_loop_best_current_path;          // najlepsza ścieżka lokalna
	vector<int> best_current_path2;         // zmienna wychodząca z minimum lokalnego (dywersyfikacja)

public:
	TabuSearch();
	TabuSearch(vector_matrix m);
	TabuSearch(vector_matrix m, int timer, int neigbourhoodMode, bool diversification, double diversificationFactor, int iteration, bool greedy, int alfa, int cadence);
	// TabuSearch(vector_matrix m, int iter, float tempC, int intIter);
	// vector<int> getRandomNeigboringSolution(vector<int> path);
	int calculatePathCost(vector<int> path);
	void find_path(vector_matrix m);
	void print_result();
	vector <int> getPath();
	// int getIterations();
	// int getInternalIterations();
	// float getInitialTempCoefficient();
	void startCounter();
	double getCounter();
	void swapNeigbour(vector<int> path);
	void invertNeigbour(vector<int> path);
	void insertNeigbour(vector<int> path);
	void copy(vector<int> path1, vector<int> path2);
	int getTimer();
	string getNeighbourMethod();
	bool getDiversification();
	int getCadence();
	int getIterations();
	int getAlfa();
	double getDiversificationFactor();
	bool getGreedy();

	vector <int> getRandomGreedyPath(int v);
};
