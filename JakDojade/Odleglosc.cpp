#include "Odleglosc.h"
#include "ListaSasiedztwa.h"
#include "UproszczonaListaMiast.h"

#include <iostream>
using namespace std;
Odleglosc::Odleglosc(int iloscMiast, ListaMiast* cel, ListaMiast* pierwszeMiasto) {
	this->cel = cel;
	this->odleglosc = 100000;
	this->previous = NULL;
}

bool Odleglosc::aktualizujOdleglosc(int odleglosc)
{
	if (this->odleglosc > odleglosc) {
		this->odleglosc = odleglosc;
		return true;
	}
	return false;
}

bool Odleglosc::aktualizujDroge(int odleglosc, ListaMiast* previous)
{
	//return this->aktualizujOdleglosc(odleglosc);
	if (this->odleglosc > odleglosc) {
		this->previous = previous;
	}
	return this->aktualizujOdleglosc(odleglosc);
}


void Odleglosc::odwiedz() {
	this->odwiedzone = true;
}