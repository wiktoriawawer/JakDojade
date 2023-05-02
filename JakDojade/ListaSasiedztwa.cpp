#include "ListaSasiedztwa.h"

#include <iostream>
using namespace std;
ListaSasiedztwa::ListaSasiedztwa(char* nazwa, int x, int y, ListaMiast* miasto)
{
	this->nazwa = nazwa;
	this->dlugoscDrogi = 0;
	this->next = NULL;
	this->x = x;
	this->y = y;
	this->miasto = miasto;
}


ListaMiast::ListaMiast(char* nazwa, int x, int y, int id)
{
	this->Sasiedztwo = new ListaSasiedztwa(nazwa,x,y, this);
	this->next = NULL;
	this->id = id;
}
