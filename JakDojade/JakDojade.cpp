#include "ListaSasiedztwa.h"
#include "Zarzadzanie.h"
#include "Mapa.h"
#include <iostream>
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
    //wczyatnie wymiarow mapy 
    int width, height, k, questions;
    cin >> naszamapa->width;
    cin >> naszamapa->height;
    Zarzadzanie* mapa=new Zarzadzanie();
    naszamapa->Wczytaj();
    naszamapa->DodajMiasta(mapa);
    naszamapa->SzukajDrog(mapa);
    mapa->wcztajLoty();
   // mapa->wypisz();
    mapa->zapytania();

   
    
    
}