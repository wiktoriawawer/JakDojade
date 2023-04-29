#pragma once
#include <iostream>

class ListaMiast;

class UproszczonaListaMiast
{
public:
	ListaMiast* miasto;
	UproszczonaListaMiast* next;

	UproszczonaListaMiast();
	UproszczonaListaMiast(ListaMiast* miasto);
	UproszczonaListaMiast(UproszczonaListaMiast* lista);

	void Dodaj(ListaMiast* miasto);
	void Wypisz();
};

