#include "Zarzadzanie.h"
#include "ListaSasiedztwa.h"
#include "OdleglosciMiasta.h"
#include "Odleglosc.h"
#include "UproszczonaListaMiast.h"
#include "Mapa.h"
#include "HashMap.h"
#include "OdlegloscLlista.h"
#include <iostream>
#include <chrono>

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
	if (ostatnieMiasto == NULL) {
		pierwszeMiasto = new ListaMiast(nazwa, x, y, iloscMiast);
		ostatnieMiasto = pierwszeMiasto;
	}
	else {
		ostatnieMiasto->next= new ListaMiast(nazwa, x, y, iloscMiast);
		ostatnieMiasto = ostatnieMiasto->next;
	}
	if (x >= 0){
		mapa->miasta[y][x] = ostatnieMiasto;
	}
	iloscMiast++;
	if (nazwa[0] != '\0') {
		Item* nowy = create_item(nazwa, ostatnieMiasto);
		listaMiast = linkedlist_insert(listaMiast, nowy);
		ht_insert(hashmapa, nazwa, ostatnieMiasto);
	}
	
}
void Zarzadzanie::dodajMiasto(int x, int y)
{
	//dodanie miasta bez nazwy 
	char* a = new char[1];
	a[0] = '\0';
	dodajMiasto(a, x, y);
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
		if (sasiedztwo2->next->miasto == miasto1) {
			sasiedztwo2->next = sasiedztwo2->next->next;
			return;
			///delele 
			//usuniecye tego maista z pamieci ---------------------
		}
		sasiedztwo2 = sasiedztwo2->next;
	}
	
}
void Zarzadzanie::dodajSasiedztwo(int x1, int y1, int x2, int y2, int odleglosc)
{
	//zakladam ze juz te miasta istanieja 
	ListaMiast* obecneMaisto1 = this->mapa->miasta[y1][x1];
	ListaMiast* obecneMaisto2 = this->mapa->miasta[y2][x2];

	if (obecneMaisto1 == NULL) {
		cout << x1 << " " << y1;
		//this->dodajMiasto(x1, y1);
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

	if (obecneMaisto2 == NULL) {
		cout << x2 << "," << y2;
		//cout << "nie udalosie " << endl;
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

void Zarzadzanie::dodajSasiedztwoLot(char* miasto1, char* miasto2, int odleglosc)
{
	//zakladam ze juz te miasta istanieja 
	//ListaMiast* obecneMaisto1 = findByName(miasto1);

	ListaMiast* obecneMaisto1 = ht_search(hashmapa, miasto1);
	
	if (obecneMaisto1 == NULL) {
		this->dodajMiasto(miasto1, -1, -1);
		dodajSasiedztwoLot(miasto1, miasto2, odleglosc);
		return;
	}
	//ListaMiast* obecneMaisto2 = findByName(miasto2);
	ListaMiast* obecneMaisto2 = ht_search(hashmapa, miasto2);
	if (obecneMaisto2 == NULL) {
		this->dodajMiasto(miasto2, -1, -1);
		dodajSasiedztwoLot(miasto1, miasto2, odleglosc);
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
	//this->wypisz();
	obecnesasiedztwo1 = obecneMaisto1->Sasiedztwo;
	while (obecnesasiedztwo1->next != NULL) {
		if (obecnesasiedztwo1->next->dlugoscDrogi > odleglosc) break;
		obecnesasiedztwo1 = obecnesasiedztwo1->next;
	}

	ListaSasiedztwa* pomocnicza = obecnesasiedztwo1->next;
	obecnesasiedztwo1->next = new ListaSasiedztwa(obecneMaisto2->Sasiedztwo->nazwa, obecneMaisto2->Sasiedztwo->x, obecneMaisto2->Sasiedztwo->y, obecneMaisto2);
	obecnesasiedztwo1->next->dlugoscDrogi = odleglosc;
	obecnesasiedztwo1->next->next = pomocnicza;
	
}

void Zarzadzanie::uproscSasiedztwo()
{

}

void Zarzadzanie::wypisz()
{
	ListaMiast* miasto = pierwszeMiasto;
	while (miasto != NULL) {
		cout << "|" << miasto->Sasiedztwo->nazwa<<","<<miasto->Sasiedztwo->x<<","<< miasto->Sasiedztwo->y << "|";
		ListaSasiedztwa* sasiedztwo = miasto->Sasiedztwo->next;
		while (sasiedztwo != NULL) {
			cout <<" - " << sasiedztwo->nazwa << " " << sasiedztwo->dlugoscDrogi<<"," << sasiedztwo->x<<"," << sasiedztwo->y << "," ;
			sasiedztwo = sasiedztwo->next;
		}
		miasto = miasto->next;
		cout << endl;
	}
}

void Zarzadzanie::dijkstraInit(char* nazwa1, char* nazwa2, bool posrednie)
{
	bool reversed = false;
	this->head = this->tail = NULL;
	
	ListaMiast* miasto1 = ht_search(hashmapa, nazwa1);
	ListaMiast* miasto2 = ht_search(hashmapa, nazwa2);
	OdleglosciMiasta* odleglosciMiasta = znajdzOdleglosciMiasta(miasto1);
	if (odleglosciMiasta == NULL) {
		odleglosciMiasta = new OdleglosciMiasta(miasto1, pierwszeMiasto, iloscMiast);
		this->odleglosciMiast[miasto1->id] = odleglosciMiasta;
		this->dijkstra(miasto1, odleglosciMiast[miasto1->id], 0);
	}
	
	//Odleglosc* odleglosc = znajdzOdlegloscDoMiasta(miasto2, odleglosciMiasta);

	odleglosciMiasta->Wypisz(miasto2,posrednie);
	/*UproszczonaListaMiast* miasta = znajdzPosrednieMiasta(miasto2, odleglosciMiasta);
	if (odleglosc == nullptr)
		return;
	cout << odleglosc->odleglosc << " ";

	miasta = miasta->next;
	if (posrednie) {
		if (reversed) {
			while (miasta != NULL && miasta->next!=NULL) {
				miasta = miasta->next;
			}
		}
		while (miasta != NULL) {
			if (compare(miasta->miasto->Sasiedztwo->nazwa,nazwa2)|| compare(miasta->miasto->Sasiedztwo->nazwa, nazwa1))
				break;
			if (miasta->miasto->Sasiedztwo->nazwa[0]!='\0')
				cout << miasta->miasto->Sasiedztwo->nazwa << ' ';
			miasta = reversed ? miasta->prev : miasta->next;
		}
	}*/
	cout << endl;
	//wypisywanie odleglosci do wszytkich miast
	//cout << "---";
	//for (int i = 0; i < iloscMiast; i++) {
	//	cout << odleglosciMiasta->odleglosci[i]->cel->Sasiedztwo->nazwa << " -";
	//	cout << odleglosciMiasta->odleglosci[i]->odleglosc << endl;
		
	//}

	
	//cout << endl;


}

void Zarzadzanie::dijkstra(ListaMiast* obecneMiasto, OdleglosciMiasta* odleglosciMiasta, int aktualnaOdleglosc)
{
	ListaSasiedztwa* sasiedztwo = obecneMiasto->Sasiedztwo;
	Odleglosc* odleglosc = znajdzOdlegloscDoMiasta(obecneMiasto, odleglosciMiasta);

	odleglosc->aktualizujDroge(aktualnaOdleglosc, NULL);
	pushListaOdleglosci(odleglosc);
	auto start = chrono::high_resolution_clock::now();
	auto stop = chrono::high_resolution_clock::now();
	while (head != NULL) {
		//start = chrono::high_resolution_clock::now();
		Odleglosc* u = head->odleglosc;
		popListaOdleglosci();
		if (u->odwiedzone) {
			continue;
		}
		u->odwiedz();
		
		ListaSasiedztwa* miasto = u->cel->Sasiedztwo->next;
		//stop = chrono::high_resolution_clock::now();
		//cout << "pop:  " << chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << endl;
		while (miasto != NULL) {
			//start = chrono::high_resolution_clock::now();
			if (miasto->y == 0) {
				int a = 0;
			}
			Odleglosc* v = znajdzOdlegloscDoMiasta(miasto->miasto, odleglosciMiasta);
			int weight = miasto->dlugoscDrogi;
			//stop = chrono::high_resolution_clock::now();
			//cout << "odleglosc:  " << chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << endl;
			//start = chrono::high_resolution_clock::now();
			if (v->aktualizujDroge(u->odleglosc + weight, u->cel)) {
				if (!v->odwiedzone) {
					pushListaOdleglosci(v);
				}
			}
			miasto = miasto->next;
			//stop = chrono::high_resolution_clock::now();
			//cout << "push and next:  " << chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count() << endl;
		}
	}


	/// stary kod
	/*
	Odleglosc* odleglosc2;
	sasiedztwo = sasiedztwo->next;
	while (sasiedztwo != NULL) {
		odleglosc2 = znajdzOdlegloscDoMiasta(sasiedztwo->miasto, odleglosciMiasta);
		int droga = aktualnaOdleglosc + sasiedztwo->dlugoscDrogi;
		
		odleglosc2->aktualizujDroge(droga, aktualnaDroga);
		odleglosc2->aktualizujOdleglosc(droga, aktualnaDroga);

		sasiedztwo = sasiedztwo->next;
	}
	while (true) {
		sasiedztwo = obecneMiasto->Sasiedztwo;
		ListaMiast* najblizszeMiasto = NULL;
		int najkrotszaDroga = 2000000;
		while (sasiedztwo != NULL) {
			odleglosc2 = znajdzOdlegloscDoMiasta(sasiedztwo->miasto, odleglosciMiasta);
			if (!odleglosc2->odwiedzone) {
				if (odleglosc2->odleglosc < najkrotszaDroga) {
					najkrotszaDroga = odleglosc2->odleglosc;
					najblizszeMiasto = sasiedztwo->miasto;
				}
			}
			sasiedztwo = sasiedztwo->next;
		}
		if (najblizszeMiasto != NULL) {
			dijkstra(najblizszeMiasto, odleglosciMiasta, najkrotszaDroga, new UproszczonaListaMiast(aktualnaDroga));
		}
		else {
			break;
		}
	}
	*/
}

Odleglosc* Zarzadzanie::znajdzOdlegloscDoMiasta(ListaMiast* miasto, OdleglosciMiasta* odleglosciMiasta) {
	return odleglosciMiasta->odleglosci[miasto->id];
}

OdleglosciMiasta* Zarzadzanie::znajdzOdleglosciMiasta(ListaMiast* miasto)
{
	return odleglosciMiast[miasto->id];
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
		this->dodajSasiedztwoLot(miasto1, miasto2, czas);
	}

}

void Zarzadzanie::OdleglosciInit() {
	this->odleglosciMiast = (OdleglosciMiasta**)calloc(iloscMiast, sizeof(OdleglosciMiasta*));
}

void Zarzadzanie::zapytania() {
	
	OdleglosciInit();
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
	ostatnieMiasto = NULL;
	listaMiast = allocate_list();
	hashmapa = create_table(HASHSIZE);

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

void Zarzadzanie::pushListaOdleglosci(Odleglosc* odleglosc)
{
	OdlegloscLlista* p, * r;
	p = new OdlegloscLlista();
	p->next = NULL;
	p->odleglosc = odleglosc;
	if (!head) head = tail = p;
	else if (head->odleglosc->odleglosc > p->odleglosc->odleglosc) {
		p->next = head;
		head = p;
	}
	else{
		r = head;
		while ((r->next) && (r->next->odleglosc->odleglosc <= p->odleglosc->odleglosc)) {
			r = r->next;
		}
		p->next = r->next;
		r->next = p;
		if (!p->next) {
			tail = p;
		}
	}
}

void Zarzadzanie::popListaOdleglosci()
{
	if (head) {
		OdlegloscLlista* p = head;
		head = head->next;
		if (!head) {
			tail = NULL;
		}
		delete(p);
	}
}
