#pragma once
class ListaMiast;

class ListaSasiedztwa
{
public:
	char* nazwa;
	int x;
	int y;
	int dlugoscDrogi;
	ListaSasiedztwa* next;
	ListaMiast* miasto;
	//dodawnie pierwszego miasta
	ListaSasiedztwa(char* nazwa, int x, int y, ListaMiast* miasto);
};

class ListaMiast {
public: 
	ListaSasiedztwa* Sasiedztwo;
	ListaMiast* next;
	//tworzenie nowego miasta
	ListaMiast(char* nazwa, int x, int y);
};
