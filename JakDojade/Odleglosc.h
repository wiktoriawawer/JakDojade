#pragma once

class ListaMiast;
class UproszczonaListaMiast;

class Odleglosc
{
public:
	ListaMiast* cel;
	UproszczonaListaMiast* droga;
	int odleglosc;
	bool odwiedzone = false;

	Odleglosc(int iloscMiast, ListaMiast* cel);
	int aktualizujOdleglosc(int odleglosc, UproszczonaListaMiast* droga);
	
	
	void odwiedz();
	void Wypisz();
};

