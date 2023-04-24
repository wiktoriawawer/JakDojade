#pragma once

class ListaMiast;

class Odleglosc
{
public:
	ListaMiast* cel;
	ListaMiast** droga;
	int odleglosc;
	bool odwiedzone = false;

public:
	Odleglosc(int iloscMiast, ListaMiast* cel);
	int aktualizujOdleglosc(int odleglosc);
	void odwiedz();
};

