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



void findRoad(Zarzadzanie* zarzadzanie, char** maps, int width, int height, int x, int y, int dlugoscdrogi) {

    if (iledrog(maps, width, height, x, y) == 0) {
        //spawdzanie czy w poblizu jesy "*"- miasto
       

    }
    

}

void readRoads(Zarzadzanie* zarzadzanie, char ** maps, int width, int height) {
    //szukanie pierwszego miasta 
    int i, j;
    for ( i = 0; i < height; i++) {
        for (j= 0; j < width; j++) {
            if (maps[i][j] == '*') {
                break;
            }
        }
        if (maps[i][j] == '*') {
            break;
        }
    }
    findRoad(zarzadzanie, maps, width, height, i, j, 0);
    



    zarzadzanie->dodajSasiedztwo(8, 1, 0, 4, 2); //gda szcz +
    zarzadzanie->dodajSasiedztwo(8, 1, 13,8,4); //gda war +

    zarzadzanie->dodajSasiedztwo(13,8, 0, 4, 6);//szcz war + 
    zarzadzanie->dodajSasiedztwo(13,8,4,14,12);//war wroc +
    zarzadzanie->dodajSasiedztwo(4,14 ,0, 4, 13); //szcz wroc + 

    zarzadzanie->dodajSasiedztwo(4, 14, 6,16, 8); //wroc opole +

    zarzadzanie->dodajSasiedztwo(4, 14, 12,14, 2);//wroc kiel
    zarzadzanie->dodajSasiedztwo(6,16, 12,14, 10);// kiel opole
    zarzadzanie->dodajSasiedztwo(12,14,10,17, 7); // kielce krk 
    
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
    mapa->wypisz();



    


    /*
    char* miasto1, * miasto2;
    miasto1 = (char*)malloc(sizeof(char) * 100);
    miasto2 = (char*)malloc(sizeof(char) * 100);
    while (true) {
        cin >> miasto1 >> miasto2;
        mapa->dijkstraInit(miasto1, miasto2, 0);
    }
    */
    
    
}