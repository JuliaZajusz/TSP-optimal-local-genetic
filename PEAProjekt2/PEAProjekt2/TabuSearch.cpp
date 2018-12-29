#include "TabuSearch.h"
#include <ctime>
#include <chrono>
#include "City.h"

TabuSearch::TabuSearch()
{
}

TabuSearch::TabuSearch(vector_matrix m)
{
	neighborhoodMatrix = m;
	path = vector<int>( m.nVertices, -10 );
	timer = 15;
	neighbourhoodMode = 2;
	diversification = true;  // domyślne włączenie dywersyfikacji
	greedy = false;
	diversificationFactor = 3;
	alfa = 10;
	cadence = 3 * m.nVertices - 1;
	iteration = 500000 * m.nVertices;
	find_path(neighborhoodMatrix);
}

TabuSearch::TabuSearch(vector_matrix m, int timer, int neighbourhoodMode, bool diversification, double diversificationFactor, int iteration, bool greedy, int alfa, int cadence)
{
	this->cadence = cadence;
	if(cadence > 3*m.nVertices - 1)
	{
		this->cadence = 3 * m.nVertices - 1;
	}
	this->alfa = alfa;
	this->greedy = greedy;
	this->iteration = iteration;
	this->diversificationFactor = diversificationFactor;
	neighborhoodMatrix = m;
	path = vector<int>(m.nVertices, -10);
	this->timer = timer;
	this->neighbourhoodMode = neighbourhoodMode;
	this->diversification = diversification;  // domyślne włączenie dywersyfikacji
	find_path(neighborhoodMatrix);
}

int TabuSearch::calculatePathCost(vector<int> path)    //<------------------------------------------------------------
{
	int cost = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		cost += neighborhoodMatrix.neighborhoodMatrix[path[i]][path[i + 1]];
	}
	cost += neighborhoodMatrix.neighborhoodMatrix[path[path.size() - 1]][path[0]];
	return cost;
}

/* uruchomienie pomiaru czasu */
void TabuSearch::startCounter() {
	counterStart = chrono::steady_clock::now();
}

/* zwraca czas pomiaru podany w ms */
double TabuSearch::getCounter() {
	auto end = chrono::steady_clock::now();
	return std::chrono::duration_cast<std::chrono::duration<double>>(end - counterStart).count() * 1000;
}

/* zamienia 2 losowe elementy(miasta) w tablicy tab[] */
void TabuSearch::swapNeigbour(vector<int> path) {
	d1 = rand() % neighborhoodMatrix.nVertices;
	d2 = rand() % neighborhoodMatrix.nVertices;
	int remember = path[d2];
	path[d2] = path[d1];
	path[d1] = remember;
}

/* odwrócenie kolejności w podciągu zaczynającym się na losowej i-tej pozycji
 * i kończącym się na losowej pozycji j-tej
 */
void TabuSearch::invertNeigbour(vector<int> path) {
	d1 = rand() % neighborhoodMatrix.nVertices;
	d2 = rand() % neighborhoodMatrix.nVertices;
	while (d1 == d2)
	{
		d2 = std::rand() % neighborhoodMatrix.nVertices;
	}
	int help = 0;
	int w1 = d1;
	int w2 = d2;
	if (w1 > w2) {
		while (w1 > w2) {
			swap(path[w1], path[w2]);
			w1--;
			w2++;
		}
		help = 1;
	}

	if (w2 > w1 && help == 0) {
		while (w2 > w1) {
			swap(path[w1], path[w2]);
			w1++;
			w2--;
		}
	}
}

/* przeniesienie losowego i-tego elementu za losową pozycję j-tą */
void TabuSearch::insertNeigbour(vector<int> path) {
	
	d1 = rand() % neighborhoodMatrix.nVertices;
	d2 = rand() % neighborhoodMatrix.nVertices;
	while (d1 == d2)
	{
		d2 = std::rand() % neighborhoodMatrix.nVertices;
	}
	int help = 0;
	if (d1 > d2) {
		for (int i = d1; i > d2; i--) {
			swap(path[i], path[i - 1]);
		}
		help = 1;
	}

	if (d2 > d1 && help == 0) {
		for (int i = d1; i < d2 - 1; i++) {
			swap(path[i], path[i + 1]);
		}
		return;
	}
}


void TabuSearch::copy(vector<int> path1, vector<int> path2) {
	for (int i = 0; i < path1.size(); i++) {
		path1[i] = path2[i];
	}
}

int TabuSearch::getTimer()
{
	return timer;
}

string TabuSearch::getNeighbourMethod()
{
	if (neighbourhoodMode == 2) {
		return "swap";
	}
	else if (neighbourhoodMode == 1) {
		return "insert";
	}
	return "invert";
}

bool TabuSearch::getDiversification()
{
	return diversification;
}

int TabuSearch::getCadence()
{
	return cadence;
}

int TabuSearch::getIterations()
{
	return iteration;
}

int TabuSearch::getAlfa()
{
	return alfa;
}

double TabuSearch::getDiversificationFactor()
{
	return diversificationFactor;
}

bool TabuSearch::getGreedy()
{
	return greedy;
}

vector<int> TabuSearch::getRandomGreedyPath(int v)
{
	vector <int> cPath(neighborhoodMatrix.nVertices,-10);
	int ** tmpTab = new int*[neighborhoodMatrix.nVertices];

	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		tmpTab[i] = new int[neighborhoodMatrix.nVertices];
	}
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
		{
			tmpTab[i][j] = neighborhoodMatrix.neighborhoodMatrix[i][j];
		}
	}


	int tmp_min = MAXINT;
	int tmp_index;

	cPath[0] = v;
	// cPath[neighborhoodMatrix.nVertices] = v;

	for (int X = 0; X < neighborhoodMatrix.nVertices; X++)
		tmpTab[X][v] = MAXINT;

	for (int N = 1; N < neighborhoodMatrix.nVertices; N++)
	{
		for (int j = 0; j < neighborhoodMatrix.nVertices; j++)
			if (tmpTab[v][j] < tmp_min)
			{
				tmp_min = tmpTab[v][j];
				tmp_index = j;
			}
		for (int X = 0; X < neighborhoodMatrix.nVertices; X++)
			tmpTab[X][tmp_index] = MAXINT;
		v = tmp_index;
		tmp_min = MAXINT;

		cPath[N] = v;
	}


	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
		delete[] tmpTab[i];
	delete[] tmpTab;

	return cPath;
}



void TabuSearch::find_path(vector_matrix m)
{	
	int numberofitteratione1 = m.nVertices;    // liczba iteracji pętli E1
	
	tabulist = new City[cadence](); // inicjalizowanie listy tabu
	current_path = vector<int>(m.nVertices, -10);       // inicjalizowanie ścieżki lokalnej
	main_loop_best_current_path = vector<int>( m.nVertices, -10 );  // inicjalizowanie najlepszej ścieżki lokalnej
	
	double current_solution = 100000000;        // zmienna zapmięitująca najlepsze lokalne rozwiązanie (pomocna przy wyjściu z minimum lokalnego)

	int numberoftabu = 0;            // liczba elementów na liście tabu

	// rozpoczęcie algorytmu – start odliczania
	startCounter();




	if(!greedy)
	{
		// wyrenderowanie losowej ścieżki jako ścieżki początkowej
	int i1 = 0, i2 = 0, remember = 0;
	for (int i = 0; i < m.nVertices; i++) {
		path[i] = i;
	}
	for (int i = 0; i < m.nVertices * 5; i++) {
		i1 = rand() % m.nVertices;
		i2 = rand() % m.nVertices;
		while (i1 == i2)
		{
			i2 = std::rand() % m.nVertices;
		}
		remember = path[i2];
		path[i2] = path[i1];
		path[i1] = remember;
	}
	} else
	{
		path = getRandomGreedyPath( rand() % neighborhoodMatrix.nVertices);
	}
	
	pathCost = calculatePathCost(path); // obliczenie kosztu przejścia ścieżki i ustawienie jej jako jako najlepszego globalnego wyniku
	current_solution = pathCost;
	
	current_path = path;											  // (zapamiętanie głównej ścieżki, ale nie zmienianie jej, żeby wyjść z minimum lokalnego)



	
	double d = 0;   // zmienna do przechowywania aktualnego czasu trwania algorytmu
	int x = 0;      // krotność czasu do wypisywania wyniku
	int r = 1 * 1000; // co ile sekund ma się wypisywać wynik (*1000)

	 // rozpoczęcie głównej pętli
	for (int j = 0; j < iteration; j++) {
		d = getCounter();
		// if (d > x*r) {
		// 	cout << "wagaSciezki path = " << calculatePathCost(path)<< endl;
		// 	print_result();
		// 	cout << "Koszt=" << pathCost << " w " << x << " sekundzie, iteracje: " << j << endl;
		// 	x++;
		// }

		// kryterium zakończenia algorytmu (timer = czas trwania algorytmu)
		if (d > timer * 1000) {
			cout << "LICZBA ITERACJI " << j << endl;
			break;
		}

		// aktualizowanie zmiennych
		double main_loop_best_current_solution = 100000000;
		d1 = 0;
		d2 = 0;


		// wewnętrzna pętla E1 – pomaga ona wyznaczyć minimum lokalne
		for (int w = 0; w < numberofitteratione1; w++) {
			bool isintabulist = false;


			// tryb sąsiedztwa
			if (neighbourhoodMode == 2) {
				swapNeigbour(current_path);
			}
			else if (neighbourhoodMode == 1) {
				insertNeigbour(current_path);
			}
			else {
				invertNeigbour(current_path);
			}

			// // obliczwanie wartości ścieżki lokalnej
			current_solution = calculatePathCost(current_path);
			
			// sprawdzanie czy wylosowane przejście pomiędzy miastami nie jest na liście tabu
			for (int m = 0; m < cadence; m++) {
				if (tabulist[m].getX() == d1 && tabulist[m].getY() == d2) {
					isintabulist = true;
					break;
				}
			}
			
			// kryterium aspiracji (jeżeli lokalny wynik * współczynnik alfa < najlepszy lokalny wynik, to pomiń listę tabu i zaktualizuj wynik
			if (current_solution * (1 + alfa * 0.01) < main_loop_best_current_solution)
				isintabulist = false;
			
			
			// funkcja oceny wartosci ruchu – jeżeli ruch nie znajduje się na liście i można polepszyć lokalny wynik,
			// to aktualizuj najlepszy lokalny wynik i ścieżkę oraz zapamiętaj miasta, które się zmieniły
			if (!isintabulist && current_solution < main_loop_best_current_solution) {
				main_loop_best_current_solution = current_solution;
				// copy(best_current_path, current_path);
				main_loop_best_current_path = current_path;
				f1 = d1;
				f2 = d2;
			}
		}
		// KONIEC PĘLTI WEWNĘTRZNEJ E1


		// aktualizowanie current_solution i path (wyników globalnych)
		if (current_solution < pathCost) {
			pathCost = current_solution;              
			path = current_path;
		}

		// dywersyfikacja (wyjście z minimum lokalnego)
		if (diversification == true) {

			
			 if (j%(int)ceil((iteration*diversificationFactor))) {

				 if (!greedy)
				 {
					 // losowanie nowej globalnej ścieżki
					 int z1 = 0, z2 = 0, rem = 0;
					 for (int i = 0; i < m.nVertices; i++) {
						 current_path[i] = i;
					 }

					 for (int i = 0; i < m.nVertices * 5; i++) {
						 z1 = rand() % m.nVertices;
						 z2 = rand() % m.nVertices;
						 while (z1 == z2)
						 {
							 z2 = std::rand() % m.nVertices;
						 }
						 rem = current_path[z2];
						 current_path[z2] = current_path[z1];
						 current_path[z1] = rem;
					 }
				 }
				 else
				 {
					 current_path = getRandomGreedyPath(rand() % neighborhoodMatrix.nVertices);
				 }
			}

		}
		// aktualizowanie tablicy tabu
		tabulist[numberoftabu].setId(numberoftabu);
		tabulist[numberoftabu].setX(f1);
		tabulist[numberoftabu].setY(f2);
		numberoftabu++;                                    // zwiększanie liczby elementów tabu
		if (numberoftabu == cadence) {                    // resetowanie liczby elementów tabu
			numberoftabu = 0;
		}
	}
}

void TabuSearch::print_result()
{
	// for (int i = 0; i < cadence; i++)
	// {
	// 	cout << "id: " << tabulist[i].getId() << ", x: " << tabulist[i].getX() << ", " << ", y: " << tabulist[i].getY() << endl;
	// }
	cout << "Sciezka: " << endl;
	for (int i = 0; i < neighborhoodMatrix.nVertices; i++)
	{
		cout << path[i] << " ";
	}
	cout << path[0] << endl;
	cout << "wagaSciezki = " << pathCost << endl;
	cout << endl;
}

vector<int> TabuSearch::getPath()
{
	return path;
}
