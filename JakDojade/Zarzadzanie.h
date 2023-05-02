#pragma once
#define HASHSIZE 3e6 + 9
class ListaMiast;
class ListaSasiedztwa;	
class OdleglosciMiasta;
class Odleglosc;
class UproszczonaListaMiast;
class Mapa;
class HashMap;
class LinkedList;
class OdlegloscLlista;
class StosDrogi;
class Zarzadzanie {
public:
	int iloscMiast;
	int iloscPoliczonychMiast=0;
	ListaMiast* pierwszeMiasto;
	ListaMiast* ostatnieMiasto;
	OdleglosciMiasta** odleglosciMiast;
	LinkedList* listaMiast;
	HashMap* hashmapa;
	Mapa* mapa;
	OdlegloscLlista* head;
	OdlegloscLlista* tail;
	//dodaj nowe miasto;
	void dodajMiasto(char* nazwa, int x, int y);
	void dodajMiasto(int x, int y);
	void usunMiasto();
	void usunSasiedztwo(ListaMiast* miasto1, ListaSasiedztwa* elementpoprzedni, ListaSasiedztwa* elementdousuniecia);
	void dodajSasiedztwo(int x1, int y1, int x2, int y2, int odleglosc);
	void dodajSasiedztwoLot(char* miasto1, char* miasto2, int odleglosc);
	void uproscSasiedztwo();
	//void dodajSasiedztwo(char* miasto1,char* miasto2 , int odleglosc);
	void wypisz();
	void dijkstraInit(char* miasto1, char* miasto2, bool posrednie);
	void dijkstra(ListaMiast* obecneMiasto, OdleglosciMiasta* odleglosciMiasta, int aktualnaOdleglosc);

	//void dijkstraInit2(char* miasto1, char* miasto2, bool posrednie);
	//void dijkstra2(ListaMiast* obecneMiasto, OdleglosciMiasta* odleglosciMiasta, int aktualnaOdleglosc, UproszczonaListaMiast* aktualnaDroga);

	Odleglosc* znajdzOdlegloscDoMiasta(ListaMiast* miasto, OdleglosciMiasta* odleglosciMiasta);
	UproszczonaListaMiast* znajdzPosrednieMiasta(ListaMiast* miasto, OdleglosciMiasta* odleglosciMiasta);
	OdleglosciMiasta* znajdzOdleglosciMiasta(ListaMiast* miasto);
	void wcztajLoty();
	void OdleglosciInit();
	void zapytania();
	char* wczytajnazwe();
	Zarzadzanie();
	ListaMiast* findByName(char* name);

	void pushListaOdleglosci(Odleglosc* odleglosc);
	void popListaOdleglosci();
	bool isEmptyListaOdleglosci();
	
	
};
