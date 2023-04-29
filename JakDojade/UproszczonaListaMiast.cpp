#include "UproszczonaListaMiast.h"
#include "ListaSasiedztwa.h"
using namespace std;
UproszczonaListaMiast::UproszczonaListaMiast()
{
	this->miasto = NULL;
	this->next = NULL;
}
UproszczonaListaMiast::UproszczonaListaMiast(ListaMiast* miasto)
{
	this->miasto = miasto;
	this->next = NULL;
}

UproszczonaListaMiast::UproszczonaListaMiast(UproszczonaListaMiast* lista)
{
	this->miasto = NULL;
	this->next = NULL;
	while (lista != NULL) {
		this->Dodaj(lista->miasto);
		lista = lista->next;
	}
}

void UproszczonaListaMiast::Dodaj(ListaMiast* miasto)
{
	if (this->miasto == NULL ) {
		this->miasto = miasto;
	}
	else if (this->next == NULL|| this->next == nullptr) {
		this->next = new UproszczonaListaMiast(miasto);
	}
	else {
		this->next->Dodaj(miasto);
	}
}

void UproszczonaListaMiast::Wypisz()
{
	UproszczonaListaMiast* obecne = this;
	obecne->next;
	while (obecne != NULL) {
		if (obecne != nullptr) {
			cout << obecne->miasto->Sasiedztwo->nazwa << ' ';
			obecne = obecne->next;
		}
		else {
			break;
		}
			
	}
	cout << endl;

}
