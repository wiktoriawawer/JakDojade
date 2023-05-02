#pragma once
#include <iostream>

class ListaMiast;
class UproszczonaListaMiast;

class Odleglosc
{
public:
	ListaMiast* cel;
	ListaMiast* previous;
	int odleglosc;
	bool odwiedzone = false;

	Odleglosc(int iloscMiast, ListaMiast* cel, ListaMiast* pierwszeMiasto);
	bool aktualizujOdleglosc(int odleglosc);

	bool aktualizujDroge(int odleglosc, ListaMiast* previous);

	void odwiedz();
};

class StosDrogi {
public:
	char* nazwa;
	StosDrogi* prev;
};

