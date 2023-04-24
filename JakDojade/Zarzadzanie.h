#pragma once
class ListaMiast;
class ListaSasiedztwa;
class OdleglosciMiasta;
class Odleglosc;

class Zarzadzanie {
public:
	int iloscMiast;
	int iloscPoliczonychMiast=0;
	ListaMiast* pierwszeMiasto;
	OdleglosciMiasta** odleglosciMiast;
	//dodaj nowe miasto;
	void dodajMiasto(char* nazwa, int x, int y);
	void usunMiasto();

	void  usunSasiedztwo(ListaMiast* miasto1, ListaSasiedztwa* elementpoprzedni, ListaSasiedztwa* elementdousuniecia);

	void dodajSasiedztwo(int x1, int y1, int x2, int y2, int odleglosc);
	void wypisz();
	void dijkstraInit(char* miasto1, char* miasto2, bool posrednie);
	void dijkstra(ListaMiast* obecneMiasto, OdleglosciMiasta* odleglosciMiasta, int odleglosc);
	Odleglosc* znajdzOdlegloscDoMiasta(ListaMiast* miasto, OdleglosciMiasta* odleglosciMiasta);
	OdleglosciMiasta* znajdzOdleglosciMiasta(ListaMiast* miasto);
	Zarzadzanie();
	ListaMiast* findByName(char* name);
	
};
