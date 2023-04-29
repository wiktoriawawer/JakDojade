#include "Odleglosc.h"
#include "ListaSasiedztwa.h"
#include "UproszczonaListaMiast.h"

#include <iostream>
using namespace std;
Odleglosc::Odleglosc(int iloscMiast, ListaMiast* cel) {
	this->cel = cel;
	this->droga = (UproszczonaListaMiast*)malloc(iloscMiast * sizeof(UproszczonaListaMiast*));
	this->odleglosc = 100000;
	
}

int Odleglosc::aktualizujOdleglosc(int odleglosc,UproszczonaListaMiast* droga)
{
	if (this->odleglosc > odleglosc) {
		this->odleglosc = odleglosc;
		this->droga = droga;
	}
	return this->odleglosc;
}

void Odleglosc::odwiedz() {
	this->odwiedzone = true;
}
void Odleglosc::Wypisz() {
	UproszczonaListaMiast* obecne = this->droga;
	obecne = obecne->next;
	while (obecne != NULL) {
		cout<<obecne->miasto->Sasiedztwo->nazwa;
		obecne = obecne->next;
	}
	cout << endl;

}