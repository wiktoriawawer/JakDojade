#pragma once
#include <iostream>
#define ROAD '#'
class Zarzadzanie;
class SzukajDrogi;
class ListaMiast;
using namespace std;
class PunktyOdwiedzone {
	public:
	int x;
	int y;
	PunktyOdwiedzone* next;
	PunktyOdwiedzone(int x, int y);
};
class Mapa
{
public :
	int width, height;
	char** tablicamapy;
	SzukajDrogi* szukanie;
	PunktyOdwiedzone* pierwszy;
	PunktyOdwiedzone* ostatni;
	ListaMiast*** miasta;

	void Wczytaj();
	void DodajMiasta(Zarzadzanie* zarzadzanie);
	void DodajSkrzyzowania(Zarzadzanie* zarzadzanie);
	void SzukajDrog(Zarzadzanie* zarzadzanie);
	void Przywroc();
	void DodajPunktyOdiwedzone(int x, int y);
	void ResetujPunktyOdwiedzone();

	void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc, bool rozwidlenie = false);
	void ZnajdzWspoldzedne(int x, int y, const char q, int tab[2], int i = 0);
	int IleDrog(int x, int y);
	int IleMiast(int x, int y);
	int IleJest(int x, int y, const char q);
	void Wypisz();

	//dla kalsy droga
	void Dodaj(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie);
	void Usun();//usuiniecie pierwszego elementu 
	void Szukaj(Zarzadzanie* zarzadznie, int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie); 
};
