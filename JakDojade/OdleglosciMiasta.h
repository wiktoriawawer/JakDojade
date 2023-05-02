#pragma once
class ListaMiast;
class Odleglosc;
class OdleglosciMiasta
{
public:
	ListaMiast* miasto;
	Odleglosc** odleglosci;
	int iloscMiast;

public:
	OdleglosciMiasta(ListaMiast* miasto, ListaMiast* pierwszeMiasto, int iloscMiast);
	void Wypisz(ListaMiast* cel, bool posrednie);
};

