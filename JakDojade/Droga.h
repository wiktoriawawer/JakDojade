#pragma once
class Droga
{
public:
	int xmiasta1;
	int ymiasta2;
	int x;
	int y;
	int xprev;
	int yprev;
	int dlugosc;
	bool rozwidlenie;
	Droga(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie);
	//~Droga();

};
class SzukajDrogi {
public:
	Droga* pierwszadroga;
	SzukajDrogi* next;
	void Dodaj(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie);
	SzukajDrogi(Droga* droga, SzukajDrogi* next);
};

