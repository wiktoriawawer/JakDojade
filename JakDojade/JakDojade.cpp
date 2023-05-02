#include "ListaSasiedztwa.h"
#include "Zarzadzanie.h"
#include "Mapa.h"
#include "HashMap.h"
#include <iostream>
#include <chrono>
#define MAXSIZE 3000

using namespace std; 

int iledrog(char** maps, int width, int height, int x, int y) {
    int ret = 0;
    if (x - 1 >= 0 && maps[x - 1][y] == '#')
        ret++;
    if (x + 1 <width && maps[x +1][y] == '#')
        ret++;
    if (y - 1 >= 0 && maps[x][y-1] == '#')
        ret++;
    if (y+1<height && maps[x][y+1] == '#')
        ret++;
    return ret;
}


int main()
{
    Mapa* naszamapa=new Mapa();

    naszamapa->szukanie = NULL;

    //wczyatnie wymiarow mapy 
    cin >> naszamapa->width;

    cin >> naszamapa->height;

    naszamapa->miasta = (ListaMiast***)calloc(naszamapa->height, sizeof(ListaMiast**));
    for (int i = 0; i < naszamapa->height; i++) {
        naszamapa->miasta[i] = (ListaMiast**)calloc(naszamapa->width, sizeof(ListaMiast*));
    }

    Zarzadzanie* mapa = new Zarzadzanie();

    mapa->mapa = naszamapa;

    auto start = chrono::high_resolution_clock::now();
    naszamapa->Wczytaj();

    //auto stop = chrono::high_resolution_clock::now();
    //cout << "krok 2: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;

    //start = chrono::high_resolution_clock::now();
    naszamapa->DodajMiasta(mapa);
    //stop = chrono::high_resolution_clock::now();
    //cout << "krok 3: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;

    //start = chrono::high_resolution_clock::now();
    naszamapa->SzukajDrog(mapa);
    //stop = chrono::high_resolution_clock::now();
    //cout << "krok 4: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;

    //naszamapa->Wypisz();
    //print_table(mapa->hashmapa);
    //mapa->wypisz();
    //cout << endl;
    //cout << mapa->iloscMiast << endl;
    
    //start = chrono::high_resolution_clock::now();
    mapa->wcztajLoty();
    //mapa->wypisz();
    //stop = chrono::high_resolution_clock::now();
    //cout << "krok 5: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;

    //start = chrono::high_resolution_clock::now();
    
    mapa->zapytania();
    //stop = chrono::high_resolution_clock::now();
    //cout << "krok 6: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;

    //auto stop = chrono::high_resolution_clock::now();
    //cout << "calosc: : " << chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << endl;
}