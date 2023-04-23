#include "ListaSasiedztwa.h"
#include <iostream>
#define MAXSIZE 3000

using namespace std; 
bool isLetter(char x) {
    if (x <= 'Z' && x >= 'A')
        return true;
    else return false; 

}

void readRoads(Zarzadzanie* zarzadzanie, char ** maps, int width, int height) {
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
    

    //wczyatnie wymiarow mapy 
    int width, height, k, questions;
    cin >> width;
    cin >> height;
    //wczytanie mapy do tablicy 
    //char maps[MAXSIZE][MAXSIZE]; 
    char** maps = (char**)malloc(height * sizeof(char*));
    for (int i = 0; i < width; i++) {
        maps[i] = (char*)malloc(width * sizeof(char));
    }


    for (int i = 0; i < height; i++) {
        //pomijanie entera
        getchar();
        for (int j = 0; j < width; j++) {
            maps[i][j] = getchar();
        }
    }

    Zarzadzanie* mapa=new Zarzadzanie();
    char* a;
    a = (char*)malloc(3 * sizeof(char*));
    a[0] = 'a';
    a[1] = 'b';
    a[2] = '\0';
    char tab[100];
    int sizeofname = 0;
    bool isname = false;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (isLetter(maps[i][j])&& !isname) {
                isname = true;
                tab[sizeofname] = maps[i][j];
                sizeofname++;
                //cityName(maps, width, height, i, j) != NULL;
                
                //mapa->dodajMiasto(a, i, j);
            }else if (isLetter(maps[i][j]) && isname) {
                tab[sizeofname] = maps[i][j];
                sizeofname++;
               
            }else if  ((!isLetter(maps[i][j]) && isname) ||(j==width-1 && isname)){
                isname = false;
                //wczyatnie i zapisanie nazwy
                a= (char*)malloc(sizeofname+1 * sizeof(char*));
                for (int w = 0; w < sizeofname; w++) {
                    a[w] = tab[w];
                }
                a[sizeofname] = '\0';
               
               // cout << a << endl;
                //szukanie gwaizdkiw poblizu 
                if (maps[i][j] == '*'){
                    mapa->dodajMiasto(a, j, i);
                    sizeofname = 0;
                    continue;
                }
                if (j - sizeofname - 1 >= 0) {
                    if (maps[i][j - sizeofname - 1] == '*') {
                        mapa->dodajMiasto(a,  j- sizeofname - 1,i);
                        sizeofname = 0;
                        continue;
                    }
                    
                }                
                for (int w = 0; w < sizeofname+2; w++) {

                    if (i - 1 >= 0) {
                        if (maps[i - 1][j - w] == '*')  {
                            mapa->dodajMiasto(a, j -w,  i - 1);
                            sizeofname = 0;
                            continue;
                        }
                    }

                    if (i + 1 < height) {
                        if (maps[i + 1][j - w] == '*') {
                            mapa->dodajMiasto(a, j - w,  i + 1);
                            sizeofname = 0;
                            continue;
                        }
                    }
                    
                }
                sizeofname = 0;
               
            }
        }
    }
    readRoads(mapa, maps, width, height);
    mapa->wypisz();


    


    // wyswietalnie mapy 
    cout << "----------------------" << endl;
    //for (int i = 0; i < height; i++) {
      //  for (int j = 0; j < width; j++) {
            //cout << maps[i][j];
      //  }
       // cout << endl;
    //}
}
