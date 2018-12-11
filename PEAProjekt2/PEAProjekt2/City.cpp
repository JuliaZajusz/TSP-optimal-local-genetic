#include "City.h"
#include <iostream>

using namespace std;

City::City() { }

// ustaw id miasta
void City::setId(int id) {
	this->id = id;
}

// ustaw x
void City::setX(int x) {
	this->x = x;
}

// ustaw y
void City::setY(int y) {
	this->y = y;
}

// zwróć id
int City::getId() {
	return id;
}

// zwróć y
int City::getY() {
	return y;
}

// zwróć x
int City::getX() {
	return x;
}

// wyświetl miasto
void City::print() {
	cout << id << " " << x << " " << y << endl;
}

// dodaj miasto o podanych id, x, y
bool City::addCity(int id, int x, int y) {
	if (x < 0 || y < 0) {
		return false;
	}

	this->id = id;
	this->x = x;
	this->y = y;

	return true;
}
