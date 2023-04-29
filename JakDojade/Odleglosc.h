#pragma once
#include <iostream>

class ListaMiast;
class UproszczonaListaMiast;

class Odleglosc
{
public:
	ListaMiast* cel;
	UproszczonaListaMiast* droga;
	int odleglosc;
	bool odwiedzone = false;

	Odleglosc(int iloscMiast, ListaMiast* cel, ListaMiast* pierwszeMiasto);
	int aktualizujOdleglosc(int odleglosc, UproszczonaListaMiast* droga);

	UproszczonaListaMiast* aktualizujDroge(int odleglosc, UproszczonaListaMiast* droga, ListaMiast* miasto = NULL);

	void odwiedz();
	void Wypisz();
};

