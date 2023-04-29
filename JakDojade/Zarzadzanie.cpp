#include "Zarzadzanie.h"
#include "ListaSasiedztwa.h"
#include "OdleglosciMiasta.h"
#include "Odleglosc.h"
#include "UproszczonaListaMiast.h"
#include <iostream>

using namespace std;

bool compare(char* x, char* y) {
	int i = 0;
	while (true) {
		if (x[i] != y[i]) {
			return false;
		}
		if (x[i] == '\0' || y[i] == '\0') {
			return true;
		}
		i++;
	}
	return true;
}


void Zarzadzanie::dodajMiasto(char* nazwa, int x, int y)
{
	iloscMiast++;
	if (pierwszeMiasto == NULL) {
		pierwszeMiasto = new ListaMiast(nazwa, x, y);
		return;
	}
	ListaMiast* obecneMaisto = pierwszeMiasto;
	while (obecneMaisto->next != NULL) {
		obecneMaisto = obecneMaisto->next;
	}
	obecneMaisto->next = new ListaMiast(nazwa, x, y);
}

void Zarzadzanie::usunMiasto()
{
}

void  Zarzadzanie::usunSasiedztwo(ListaMiast* miasto1, ListaSasiedztwa* elementpoprzedni, ListaSasiedztwa* elementdousuniecia) {
	//usuniecie sasiedztwa z pierwszej listy 
	elementpoprzedni->next = elementdousuniecia->next;
	//usuniecie tego sasiedztwa z pamieci --------------- 
	//abc 
	ListaSasiedztwa* sasiedztwo2 = elementdousuniecia->miasto->Sasiedztwo;
	while (sasiedztwo2->next != NULL) {
		if (sasiedztwo2->next->miasto = miasto1) {
			sasiedztwo2->next = sasiedztwo2->next->next;
			///delele 
			//usuniecye tego maista z pamieci ---------------------
		}
	}
	
}
void Zarzadzanie::dodajSasiedztwo(int x1, int y1, int x2, int y2, int odleglosc)
{
	//zakladam ze juz te miasta istanieja 
	ListaMiast* obecneMaisto1 = pierwszeMiasto;
	while (true) {
		if (obecneMaisto1->Sasiedztwo->x == x1 && obecneMaisto1->Sasiedztwo->y == y1) 
				break;
		obecneMaisto1 = obecneMaisto1->next;
		if (obecneMaisto1 == NULL) break;

	}
	if (obecneMaisto1 == NULL) {
		cout << "nie udalosie " << endl;
		return;
	}
	ListaSasiedztwa* obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	//sprawdzam czy istnieje juz takie sasiedztwo 
	while (obecnesasiedztwo1->next != NULL) {
		if (obecnesasiedztwo1->next->x == x2 && obecnesasiedztwo1->next->y == y2) {
			//jezeli obecne sasiedztwo jest mnijsze to wychodzimy z funkcji 
			if (obecnesasiedztwo1->next->dlugoscDrogi <= odleglosc)
				return;
			else {
				//jezeli obecne sasziedztwo jesy wieksze to je usuwamy 
				this->usunSasiedztwo(obecneMaisto1, obecnesasiedztwo1, obecnesasiedztwo1->next);
				break;
			}
		}
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}

	obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	while (obecnesasiedztwo1->next != NULL) {
		if (obecnesasiedztwo1->next->dlugoscDrogi > odleglosc) break;
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}


	//szuaknie 2 miasta 
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
		if (obecnesasiedztwo2->next->dlugoscDrogi > odleglosc) break;
		obecnesasiedztwo2 = obecnesasiedztwo2->next;
	}

	ListaSasiedztwa* pomocnicza = obecnesasiedztwo1->next;
	obecnesasiedztwo1->next = new ListaSasiedztwa(obecneMaisto2->Sasiedztwo->nazwa, x2, y2, obecneMaisto2);
	obecnesasiedztwo1->next->dlugoscDrogi = odleglosc;
	obecnesasiedztwo1->next->next = pomocnicza;
	pomocnicza = obecnesasiedztwo2->next;
	obecnesasiedztwo2->next = new ListaSasiedztwa(obecneMaisto1->Sasiedztwo->nazwa, x1, y1, obecneMaisto1);
	obecnesasiedztwo2->next->dlugoscDrogi = odleglosc;
	obecnesasiedztwo2->next->next = pomocnicza;

}

void Zarzadzanie::dodajSasiedztwo(char* miasto1, char* miasto2, int odleglosc)
{
	//zakladam ze juz te miasta istanieja 
	ListaMiast* obecneMaisto1 = findByName(miasto1);
	
	if (obecneMaisto1 == NULL) {
		this->dodajMiasto(miasto1, -1, -1);
		dodajSasiedztwo(miasto1, miasto2, odleglosc);
		return;
	}
	ListaMiast* obecneMaisto2 = findByName(miasto2);
	if (obecneMaisto2 == NULL) {
		this->dodajMiasto(miasto2, -1, -1);
		dodajSasiedztwo(miasto1, miasto2, odleglosc);
		return;
	}
		
	
	ListaSasiedztwa* obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	//sprawdzam czy istnieje juz takie sasiedztwo 
	while (obecnesasiedztwo1->next != NULL) {
		if (compare(obecnesasiedztwo1->next->nazwa,miasto2)) {
			//jezeli obecne sasiedztwo jest mnijsze to wychodzimy z funkcji 
			if (obecnesasiedztwo1->next->dlugoscDrogi <= odleglosc)
				return;
			else {
				//jezeli obecne sasziedztwo jesy wieksze to je usuwamy 
				this->usunSasiedztwo(obecneMaisto1, obecnesasiedztwo1, obecnesasiedztwo1->next);
				break;
			}
		}
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}

	obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	while (obecnesasiedztwo1->next != NULL) {
		if (obecnesasiedztwo1->next->dlugoscDrogi > odleglosc) break;
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}

	ListaSasiedztwa* obecnesasiedztwo2 = obecneMaisto2->Sasiedztwo;
	while (obecnesasiedztwo2->next != NULL) {
		if (obecnesasiedztwo2->next->dlugoscDrogi > odleglosc) break;
		obecnesasiedztwo2 = obecnesasiedztwo2->next;
	}

	ListaSasiedztwa* pomocnicza = obecnesasiedztwo1->next;
	obecnesasiedztwo1->next = new ListaSasiedztwa(obecneMaisto2->Sasiedztwo->nazwa, obecneMaisto2->Sasiedztwo->x, obecneMaisto2->Sasiedztwo->y, obecneMaisto2);
	obecnesasiedztwo1->next->dlugoscDrogi = odleglosc;
	obecnesasiedztwo1->next->next = pomocnicza;
	pomocnicza = obecnesasiedztwo2->next;
	obecnesasiedztwo2->next = new ListaSasiedztwa(obecneMaisto1->Sasiedztwo->nazwa, obecneMaisto1->Sasiedztwo->x, obecneMaisto1->Sasiedztwo->y, obecneMaisto1);
	obecnesasiedztwo2->next->dlugoscDrogi = odleglosc;
	obecnesasiedztwo2->next->next = pomocnicza;


}

void Zarzadzanie::wypisz()
{
	ListaMiast* miasto = pierwszeMiasto;
	while (miasto != NULL) {
		cout << "|" << miasto->Sasiedztwo->nazwa << ",x=" << miasto->Sasiedztwo->x << ",y=" << miasto->Sasiedztwo->y << "|-";
		ListaSasiedztwa* sasiedztwo = miasto->Sasiedztwo->next;
		while (sasiedztwo != NULL) {
			cout << sasiedztwo->nazwa << " " << sasiedztwo->dlugoscDrogi << ",x=" << sasiedztwo->x << ",y=" << sasiedztwo->y << "-";
			sasiedztwo = sasiedztwo->next;
		}
		miasto = miasto->next;
		cout << endl;
	}
}

void Zarzadzanie::dijkstraInit(char* nazwa1, char* nazwa2, bool posrednie)
{
	ListaMiast* miasto1 = findByName(nazwa1);
	ListaMiast* miasto2 = findByName(nazwa2);
	OdleglosciMiasta* odleglosciMiasta = znajdzOdleglosciMiasta(miasto1);
	if (odleglosciMiasta == NULL) {
		odleglosciMiasta = znajdzOdleglosciMiasta(miasto2);
		if (odleglosciMiasta == NULL) {
			odleglosciMiasta = new OdleglosciMiasta(miasto1, pierwszeMiasto, iloscMiast);
			this->odleglosciMiast[iloscPoliczonychMiast] = odleglosciMiasta;
			this->dijkstra(miasto1, odleglosciMiast[iloscPoliczonychMiast], 0, new UproszczonaListaMiast(miasto1));
		}
		else {
			ListaMiast* tmp = miasto1;
			miasto1 = miasto2;
			miasto2 = tmp;
		}
	}
	
	Odleglosc* odleglosc = znajdzOdlegloscDoMiasta(miasto2, odleglosciMiasta);
	if (odleglosc == nullptr)
		return;
	cout << odleglosc->odleglosc;
	odleglosc->Wypisz();


}

void Zarzadzanie::dijkstra(ListaMiast* obecneMiasto, OdleglosciMiasta* odleglosciMiasta, int aktualnaOdleglosc, UproszczonaListaMiast* aktualnaDroga)
{
	ListaSasiedztwa* sasiedztwo = obecneMiasto->Sasiedztwo;
	Odleglosc* odleglosc = znajdzOdlegloscDoMiasta(sasiedztwo->miasto, odleglosciMiasta);
	odleglosc->odwiedz();
	aktualnaOdleglosc = odleglosc->aktualizujOdleglosc(aktualnaOdleglosc,aktualnaDroga);
	sasiedztwo = sasiedztwo->next;
	while (sasiedztwo != NULL) {
		odleglosc = znajdzOdlegloscDoMiasta(sasiedztwo->miasto, odleglosciMiasta);
		int droga = aktualnaOdleglosc + sasiedztwo->dlugoscDrogi;
		odleglosc->aktualizujOdleglosc(droga, aktualnaDroga);
		sasiedztwo = sasiedztwo->next;
	}
	sasiedztwo = obecneMiasto->Sasiedztwo;
	while (sasiedztwo != NULL) {
		odleglosc = znajdzOdlegloscDoMiasta(sasiedztwo->miasto, odleglosciMiasta);
		int droga = aktualnaOdleglosc + sasiedztwo->dlugoscDrogi;
		if (!odleglosc->odwiedzone) {
			dijkstra(sasiedztwo->miasto, odleglosciMiasta ,droga, aktualnaDroga);
		}
		sasiedztwo = sasiedztwo->next;
	}
}

Odleglosc* Zarzadzanie::znajdzOdlegloscDoMiasta(ListaMiast* miasto, OdleglosciMiasta* odleglosciMiasta) {
	for (int i = 0; i < iloscMiast; i++) {
		if (odleglosciMiasta->odleglosci[i]->cel == miasto) {
			return odleglosciMiasta->odleglosci[i];
		}
	}
	return NULL;
}

OdleglosciMiasta* Zarzadzanie::znajdzOdleglosciMiasta(ListaMiast* miasto)
{
	return nullptr;
}

void Zarzadzanie::wcztajLoty()
{
	char* miasto1, * miasto2;
	int k, czas;
	cin >> k;
	char* zrodlo, * cel;
	for (int i = 0; i < k; i++) {
		miasto1 = (char*)malloc(sizeof(char) * 100);
		miasto2 = (char*)malloc(sizeof(char) * 100);
		cin >> miasto1;
		cin >> miasto2;
		cin >> czas;
		this->dodajSasiedztwo(miasto1, miasto2, czas);
	}

}
void Zarzadzanie::zapytania() {
	char* miasto1, * miasto2;
		
	int q, typ;
	cin >> q;
	char* zrodlo, * cel;
	for (int i = 0; i < q; i++) {
		miasto1 = (char*)malloc(sizeof(char) * 100);
		miasto2 = (char*)malloc(sizeof(char) * 100);
		cin >> miasto1;
		cin >> miasto2;
		cin >> typ;
		this->dijkstraInit(miasto1, miasto2, typ);
	}
}
char* Zarzadzanie::wczytajnazwe() {
	char x;
	char tab[100];
	int i = 0;
	while (true) {
		x = getchar();
		if (x == ' ')
			break;
		tab[i] = x;
		i++;
	}
	char* ret = (char*)malloc(i * sizeof(char));
	for (int j = 0; j < i; j++) {
		ret[i] = tab[i];
	}
	return ret;

}

Zarzadzanie::Zarzadzanie()
{
	iloscMiast = 0;
	pierwszeMiasto = NULL;
	this->odleglosciMiast = (OdleglosciMiasta**)malloc(iloscMiast * sizeof(OdleglosciMiasta*));
}


ListaMiast* Zarzadzanie::findByName(char* name) {
	ListaMiast* obecneMaisto = pierwszeMiasto;
	while (true) {
		if (obecneMaisto == NULL)
			break;
		if (compare(obecneMaisto->Sasiedztwo->nazwa, name))
			break;
		obecneMaisto = obecneMaisto->next;
	}
	return obecneMaisto;
}
