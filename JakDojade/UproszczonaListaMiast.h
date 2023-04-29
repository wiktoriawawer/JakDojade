#pragma once
#include <iostream>

class ListaMiast;

class UproszczonaListaMiast
{
public:
	ListaMiast* miasto;
	UproszczonaListaMiast* next;

	UproszczonaListaMiast(ListaMiast* miasto);

	void Dodaj(ListaMiast* miasto);
};

