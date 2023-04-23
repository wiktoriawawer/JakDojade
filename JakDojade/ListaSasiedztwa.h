#pragma once
class ListaSasiedztwa
{
public:
	char* nazwa;
	int x;
	int y;
	int dlugoscDrogi;
	ListaSasiedztwa* next;
	//dodawnie pierwszego miasta
	ListaSasiedztwa(char* nazwa, int x, int y);
};

class ListaMiast {
public: 
	ListaSasiedztwa* Sasiedztwo;
	ListaMiast* next;
	//tworzenie nowego miasta
	ListaMiast(char* nazwa, int x, int y);
};

class Zarzadzanie {
public:
	int iloscMiast;
	ListaMiast* pierwszeMiasto;
	//dodaj nowe miasto;
	void dodajMiasto(char* nazwa,  int x, int y);
	void usunMiasto();
	void dodajSasiedztwo( int x1, int y1, int x2, int y2, int odleglosc);
	void wypisz();
	Zarzadzanie();
};

