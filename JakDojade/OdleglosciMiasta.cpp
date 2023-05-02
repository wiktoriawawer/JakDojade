#include "odleglosciMiasta.h"
#include "Odleglosc.h"
#include "ListaSasiedztwa.h"
#include <iostream>

OdleglosciMiasta::OdleglosciMiasta(ListaMiast* miasto, ListaMiast* pierwszeMiasto, int iloscMiast)
{
	this->miasto = miasto;
	this->iloscMiast = iloscMiast;
	odleglosci = (Odleglosc**)malloc(iloscMiast * sizeof(Odleglosc*));
	ListaMiast* obecneMiasto = pierwszeMiasto;
	while(obecneMiasto!=NULL) {
		odleglosci[obecneMiasto->id] = new Odleglosc(iloscMiast, obecneMiasto, pierwszeMiasto);
		obecneMiasto = obecneMiasto->next;
	}
}

void OdleglosciMiasta::Wypisz(ListaMiast* cel,bool posrednie)
{
	StosDrogi* stos = new StosDrogi();
	stos->nazwa = NULL;
	stos->prev = NULL;
	Odleglosc* obecne = odleglosci[cel->id];
	
	int odleglosc = obecne->odleglosc;
	
	std::cout << odleglosc <<" ";
	if (posrednie) {
		while (obecne->previous != NULL) {
			stos->nazwa = obecne->previous->Sasiedztwo->nazwa;
			if (stos->nazwa[0] != '\0') {
				StosDrogi* tmp = new StosDrogi();
				tmp->prev = stos;
				stos = tmp;
			}	
			obecne = odleglosci[obecne->previous->id];
		}
		if (stos->prev == NULL || stos->prev->prev == NULL) {
			return;
		}
		stos = stos->prev->prev;
		while (stos != NULL) {
			std::cout << stos->nazwa << " ";
			stos = stos->prev;
		}
	}
	

}
