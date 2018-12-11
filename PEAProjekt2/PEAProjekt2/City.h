#pragma once

#include <stdio.h>

class City {
private:
	int id;     // id miasta
	int x, y;   // współrzędne miasta

public:
	City();
	void setId(int id);                 // ustaw id miasta
	void setX(int x);                   // ustaw x
	void setY(int y);                   // ustaw y
	int getId();                        // zwróć id
	int getX();                         // zwróć x
	int getY();                         // zwróć y
	void print();                       // wyświetl miasto
	bool addCity(int id, int x, int y); // dodaj miasto o podanych id, x, y
};
