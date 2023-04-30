#include "Droga.h"
#include<iostream>

void SzukajDrogi::Dodaj(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc,bool rozwidlenie)
{
	if (pierwszadroga == NULL) {
		pierwszadroga = new Droga(xm, ym, x, y, xprev, yprev, dlugosc, rozwidlenie);
		next = NULL;
		return;
	}
	SzukajDrogi* obecna = this;
	while (obecna->next != NULL) {
		obecna = obecna->next;
	}
	obecna->next = new SzukajDrogi(new Droga(xm, ym, x, y, xprev, yprev, dlugosc, rozwidlenie), NULL);

}
SzukajDrogi::SzukajDrogi(Droga* droga, SzukajDrogi* next) {
	this->next = next;
	this->pierwszadroga = droga;

}

Droga::Droga(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie)
{
	this->xmiasta1 = xm;
	this->ymiasta2 = ym;
	this->x = x;
	this->y = y;
	this->xprev = xprev;
	this->yprev = yprev;
	this->dlugosc = dlugosc;
	this->rozwidlenie = rozwidlenie;

}
