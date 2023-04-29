#include "UproszczonaListaMiast.h"

UproszczonaListaMiast::UproszczonaListaMiast(ListaMiast* miasto)
{
	this->miasto = miasto;
	this->next = NULL;
}

void UproszczonaListaMiast::Dodaj(ListaMiast* miasto)
{
	if (next == NULL) {
		this->next = new UproszczonaListaMiast(miasto);
	}
	else {
		this->next->Dodaj(miasto);
	}
}
