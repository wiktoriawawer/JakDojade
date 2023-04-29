#include "Odleglosc.h"
#include "ListaSasiedztwa.h"
#include "UproszczonaListaMiast.h"

#include <iostream>
using namespace std;
Odleglosc::Odleglosc(int iloscMiast, ListaMiast* cel, ListaMiast* pierwszeMiasto) {
	this->cel = cel;
	this->droga = (UproszczonaListaMiast*)malloc(iloscMiast * sizeof(UproszczonaListaMiast*));
	this->odleglosc = 100000;
	this->droga = new UproszczonaListaMiast();
	
}

int Odleglosc::aktualizujOdleglosc(int odleglosc,UproszczonaListaMiast* droga)
{
	if (this->odleglosc > odleglosc) {
		this->odleglosc = odleglosc;
		//this->droga = droga;
	}
	return this->odleglosc;
}

UproszczonaListaMiast* Odleglosc::aktualizujDroge(int odleglosc, UproszczonaListaMiast* droga, ListaMiast* miasto)
{
	if (this->odleglosc > odleglosc) {
		this->droga = new UproszczonaListaMiast(droga);
	}
	if (miasto != NULL) {
		this->droga->Dodaj(miasto);
	}
	return this->droga;
}


void Odleglosc::odwiedz() {
	this->odwiedzone = true;
}
void Odleglosc::Wypisz() {
	UproszczonaListaMiast* obecne = this->droga;
	obecne = obecne->next;
	while (obecne != NULL) {
		cout<<obecne->miasto->Sasiedztwo->nazwa<<' ';
		obecne = obecne->next;
	}
	cout << endl;

}