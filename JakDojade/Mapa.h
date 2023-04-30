#pragma once
#include <iostream>
#define ROAD '#'
class Zarzadzanie;
class SzukajDrogi;
using namespace std;
class Mapa
{
public :
	int width, height;
	char** tablicamapy;
	SzukajDrogi* szukanie;
	void Wczytaj();
	void DodajMiasta(Zarzadzanie* zarzadzanie);
	void SzukajDrog(Zarzadzanie* zarzadzanie);
	void Przywroc();
	//void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc);
	void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc, bool* todelete);
	//void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc, int todelete);
	//void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc);
	void SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc, bool rozwidlenie = false);
	int* ZnajdzWspoldzedne(int x, int y, const char q, int i = 0);
	int IleDrog(int x, int y);
	int IleMiast(int x, int y);
	int IleJest(int x, int y, const char q);
	void Wypisz();

	//dla kalsy droga
	void Dodaj(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie);
	void Usun();//usuiniecie pierwszego elementu 
	void Szukaj(Zarzadzanie* zarzadznie, int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie); 
};