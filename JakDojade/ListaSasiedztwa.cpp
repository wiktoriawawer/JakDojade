#include "ListaSasiedztwa.h"

#include <iostream>
using namespace std;
ListaSasiedztwa::ListaSasiedztwa(char* nazwa, int x, int y)
{
	this->nazwa = nazwa;
	this->dlugoscDrogi = 0;
	this->next = NULL;
	this->x = x;
	this->y = y;

}


ListaMiast::ListaMiast(char* nazwa, int x, int y)
{
	this->Sasiedztwo = new ListaSasiedztwa(nazwa,x,y);
	this->next = NULL;
}
void Zarzadzanie::dodajMiasto(char* nazwa, int x, int y)
{
	iloscMiast++;
	if (pierwszeMiasto == NULL) {
		pierwszeMiasto = new ListaMiast(nazwa,x,y);
		return;
	}
	ListaMiast* obecneMaisto = pierwszeMiasto;
	while (obecneMaisto->next != NULL) {
		obecneMaisto = obecneMaisto->next;
	}
	obecneMaisto->next= new ListaMiast(nazwa,x,y);
}

void Zarzadzanie::usunMiasto()
{
}

void Zarzadzanie::dodajSasiedztwo(int x1, int y1, int x2, int y2, int odleglosc)
{
	//zakladam ze juz te miasta istanieja 
	ListaMiast* obecneMaisto1 = pierwszeMiasto;
	while (true) {
		if (obecneMaisto1->Sasiedztwo->x == x1 && obecneMaisto1->Sasiedztwo->y == y1) break;
		obecneMaisto1 = obecneMaisto1->next;
		if (obecneMaisto1 == NULL) break;

	}
	if (obecneMaisto1 == NULL) {
		cout << "nie udalosie " << endl;
		return;
	}
	ListaSasiedztwa* obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	while (obecnesasiedztwo1->next != NULL) {
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}
	

	ListaMiast* obecneMaisto2 = pierwszeMiasto;
	while (true) {
		if (obecneMaisto2->Sasiedztwo->x == x2 && obecneMaisto2->Sasiedztwo->y == y2) break;
		obecneMaisto2 = obecneMaisto2->next;
		if (obecneMaisto2 == NULL) break;
	}
	if (obecneMaisto2 == NULL) {
		cout << "nie udalosie " << endl;
		return;
	}
	ListaSasiedztwa* obecnesasiedztwo2 = obecneMaisto2->Sasiedztwo;
	while (obecnesasiedztwo2->next != NULL) {
		obecnesasiedztwo2 = obecnesasiedztwo2->next;
	}

	obecnesasiedztwo1->next = new ListaSasiedztwa(obecneMaisto2->Sasiedztwo->nazwa, x2, y2);
	obecnesasiedztwo1->next->dlugoscDrogi = odleglosc;

	obecnesasiedztwo2->next = new ListaSasiedztwa(obecneMaisto1->Sasiedztwo->nazwa,x1,y1);
	obecnesasiedztwo2->next->dlugoscDrogi = odleglosc;

}

void Zarzadzanie::wypisz()
{
	ListaMiast* miasto = pierwszeMiasto;
	while (miasto != NULL) {
		cout << "|" << miasto->Sasiedztwo->nazwa <<",x="<< miasto->Sasiedztwo->x<< ",y=" << miasto->Sasiedztwo->y << "|-";
		ListaSasiedztwa* sasiedztwo = miasto->Sasiedztwo->next;
		while (sasiedztwo != NULL) {
			cout << sasiedztwo->nazwa<<" " << sasiedztwo->dlugoscDrogi<<",x="<<sasiedztwo->x <<",y="<<sasiedztwo->y << "-";
			sasiedztwo = sasiedztwo->next;
		}
		miasto = miasto->next;
		cout << endl;
	}
}

Zarzadzanie::Zarzadzanie()
{
	iloscMiast = 0;
	pierwszeMiasto = NULL;
}
