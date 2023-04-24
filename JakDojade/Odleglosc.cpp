#include "Odleglosc.h"
#include "ListaSasiedztwa.h"
#include <iostream>

Odleglosc::Odleglosc(int iloscMiast, ListaMiast* cel) {
	this->cel = cel;
	this->droga = (ListaMiast**)malloc(iloscMiast * sizeof(ListaMiast*));
	this->odleglosc = 100000;
	
}

int Odleglosc::aktualizujOdleglosc(int odleglosc)
{
	if (this->odleglosc > odleglosc) {
		this->odleglosc = odleglosc;
	}
	return this->odleglosc;
}

void Odleglosc::odwiedz() {
	this->odwiedzone = true;
}
