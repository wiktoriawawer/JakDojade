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
	for (int i = 0; i < iloscMiast; i++) {
		odleglosci[i] = new Odleglosc(iloscMiast, obecneMiasto, pierwszeMiasto);
		obecneMiasto = obecneMiasto->next;
	}
}
