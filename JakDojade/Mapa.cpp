#include "Mapa.h"
#include "Zarzadzanie.h"
#include "Droga.h"
#include <chrono>
bool isLetter(char x)
{
    if (x <= 'Z' && x >= 'A')
        return true;
    if (x >= '0' && x <= '9')
        return true;
    else return false;
}


void Mapa::Wczytaj() {
	//alokacja pamieci 
	tablicamapy = (char**)malloc(this->height * sizeof(char*));
	for (int i = 0; i < this->height; i++) {
		tablicamapy[i] = (char*)malloc(width * sizeof(char));
	}
	//wczytanie mapy 
	for (int i = 0; i < this->height; i++) {
		//pomijanie entera
 		getchar();
		for (int j = 0; j < this->width; j++) {
			tablicamapy[i][j] = getchar();
		}
	}

}

void Mapa::DodajMiasta(Zarzadzanie* zarzadzanie)
{
    char* a;
    char tab[100];
    int sizeofname = 0;
    bool isname = false;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (isLetter(this->tablicamapy[i][j])&& !isname) {
                isname = true;
                tab[sizeofname] = tablicamapy[i][j];
                sizeofname++;
            }else if (isLetter(this->tablicamapy[i][j]) && isname) {
                tab[sizeofname] = this->tablicamapy[i][j];
                sizeofname++;
               
            }if  ((!isLetter(this->tablicamapy[i][j]) && isname) ||(j== this->width-1 && isname)){
                isname = false;
                //wczyatnie i zapisanie nazwy
                a= (char*)malloc(sizeofname+1 * sizeof(char*));
                for (int w = 0; w < sizeofname; w++) {
                    a[w] = tab[w];
                }
                a[sizeofname] = '\0';

                //szukanie gwaizdkiw poblizu 
                int left = j - sizeofname - (j == this->width - 1 ? 0 : 1);
                if (this->tablicamapy[i][j] == '*'){
                    zarzadzanie->dodajMiasto(a, j, i);
                    sizeofname = 0;
                    continue;
                }
                else if (j - sizeofname - 1 >= 0) {
                    if (this->tablicamapy[i][left] == '*') {
                        zarzadzanie->dodajMiasto(a,  left,i);
                        sizeofname = 0;
                        continue;
                    }
                    
                }  
                for (int w = 0; w < sizeofname + 2; w++) {

                    if (i - 1 >= 0) {
                        if (this->tablicamapy[i - 1][j - w] == '*') {
                            zarzadzanie->dodajMiasto(a, j - w, i - 1);
                            sizeofname = 0;
                            continue;
                        }
                    }

                    if (i + 1 < this->height) {
                        if (this->tablicamapy[i + 1][j - w] == '*') {
                            zarzadzanie->dodajMiasto(a, j - w, i + 1);
                            sizeofname = 0;
                            continue;
                        }
                    }

                }
                sizeofname = 0;
            }
        }
    }
    DodajSkrzyzowania(zarzadzanie);
    //this->Wypisz();
}

void Mapa::DodajSkrzyzowania(Zarzadzanie* zarzadzanie)
{
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (tablicamapy[i][j] == '#') {
                //if (IleDrog(j, i) > 2) {
                    tablicamapy[i][j] = '*';
                    zarzadzanie->dodajMiasto(j, i);
                //}

            }
        }
    }


}

void Mapa::SzukajDrog(Zarzadzanie* zarzadzanie)
{
    //szukanie pierwszego miasta 
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (tablicamapy[i][j] == '*') {
                tablicamapy[i][j] = '.';
                //cout << j << " " << i << endl;
                //this->Szukaj(zarzadzanie, j, i, j, i, j, i, 0, 0);
                this->SzukajDrogi(zarzadzanie, j, i, j, i, 0);
                //cout << j << " " << i << endl;
                //this->Wypisz(); 
                //cout << endl;
                //cout << endl;
                this->Przywroc();

            }
        }
        
    }

   
}


void Mapa::Przywroc() {
    /*
    int i, j;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (tablicamapy[i][j] == '&') {
                tablicamapy[i][j] = '#';
            }
        }
    }
    */
    PunktyOdwiedzone* obecny = pierwszy;
    while (obecny != NULL) {
        tablicamapy[obecny->y][obecny->x] = '#';
        obecny = obecny->next;
    }
    //trzeba tu zwalniac pamiec tych punktow odiwedzonych 
    pierwszy = NULL;
    ostatni = NULL;
}

void Mapa::DodajPunktyOdiwedzone(int x, int y )
{
    if (ostatni == NULL) {
        pierwszy = new PunktyOdwiedzone(x, y);
        ostatni = pierwszy;
    }
    else {
        ostatni->next= new PunktyOdwiedzone(x, y);
        ostatni = ostatni->next;

    }
}

void Mapa::ResetujPunktyOdwiedzone()
{
    
}

void Mapa::SzukajDrogi(Zarzadzanie* zarzadznie, int xmiasta1, int ymiasta1, int x, int y, int dlugosc, bool rozwidlenie)
{
    int ileMiast = IleMiast(x, y);
    int ileDrog = IleDrog(x, y);
    
    if (x < -1) {
        int a = 0;
    }
    if (ileMiast == 0 && ileDrog == 0) {
        tablicamapy[y][x] = rozwidlenie ? '&' : '.';
        return;
    }
    else if (ileMiast == 0 && ileDrog == 1)
    {
        int tab[2] = { -1,-1 };
        
        ZnajdzWspoldzedne(x, y, '#', tab);
        if (tab[0] == -1 || tab[1] == -1)
            return;
        
        if (rozwidlenie) {
            DodajPunktyOdiwedzone(x, y);
            tablicamapy[y][x] = '&';

        }
        else {
            tablicamapy[y][x] = '.';
        }
        SzukajDrogi(zarzadznie, xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1, rozwidlenie);
        return;

    }
    else if (ileMiast == 0 && ileDrog >1)
    {   
        for (int i = 0; i < ileDrog; i++) {
            int tab[2] = { -1,-1 };
            ZnajdzWspoldzedne(x, y, '#', tab, i);
            if (tab[0] == -1 || tab[1] == -1)
                return;
            if (tablicamapy[y][x] == '#' || tablicamapy[y][x] == '&') {
                DodajPunktyOdiwedzone(x, y);
                tablicamapy[y][x] = '&';
            }
            else {
                tablicamapy[y][x] = '.';
            }
            SzukajDrogi(zarzadznie, xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1, true);

        }
        return;
        
    }
    else if (ileMiast==1 && ileDrog==0) {
        int tab[2] = { -1,-1 }; 
        ZnajdzWspoldzedne(x, y, '*', tab);
        if (tab[0] == -1 || tab[1] == -1)
            return;

        if (tablicamapy[y][x] == '#' || tablicamapy[y][x] == '&') {
            tablicamapy[y][x] = rozwidlenie ? '&' : '.';
            if (rozwidlenie)
                DodajPunktyOdiwedzone(x, y);
        }
        else {
            tablicamapy[y][x] = '.';
        }
        zarzadznie->dodajSasiedztwo(xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1);
        return;
    } 
    else if (ileMiast >0   && ileDrog > 0) { 
        rozwidlenie = ileDrog + ileMiast > 1 || rozwidlenie ? true : false;
        
        for (int i = 0; i < ileMiast; i++) {
            int tab[2] = { -1,-1 }; 
            ZnajdzWspoldzedne(x, y, '*', tab);
            if (tab[0] == -1 || tab[1] == -1)
                return;
            zarzadznie->dodajSasiedztwo(xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1);
        }

       //? this->tablicamapy[y][x] = '.';
        
        for (int i = 0; i < ileDrog; i++) {
            int tab[2] = { -1,-1 };
            ZnajdzWspoldzedne(x, y, '#', tab);
            if (tab[0] == -1 || tab[1] == -1)
                return;               
            else if (tablicamapy[y][x] == '#' || tablicamapy[y][x] == '&') {
                tablicamapy[y][x] = rozwidlenie ? '&' : '.';
                if (rozwidlenie)
                    DodajPunktyOdiwedzone(x, y);
            }
            else {
                tablicamapy[y][x] = '.';
            }
            SzukajDrogi(zarzadznie, xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1, rozwidlenie);

        }


    }
    else if (ileMiast >1 && ileDrog == 0) {
        for (int i = 0; i < ileMiast ; i++) {
            int tab[2] = { -1,-1 };
            ZnajdzWspoldzedne(x, y, '*', tab, i);
            zarzadznie->dodajSasiedztwo(xmiasta1, ymiasta1, tab[0], tab[1], dlugosc + 1);
        }
    }
 

    

    
}
void Mapa::ZnajdzWspoldzedne(int x, int y,const char q, int tab[2], int i) {
    if (x - 1 >= 0 && this->tablicamapy[y][x - 1] == q) {
        tab[0] = x - 1;
        tab[1] = y;
        if (i == 0) {
            return;
        }
        else {
            i--;
        }
    }
    if (x + 1 < width && tablicamapy[y][x + 1] == q) {
        tab[0] = x + 1;
        tab[1] = y;
        if (i == 0) {
            return;
        }
        else {
            i--;
        }
    }

    if (y - 1 >= 0 && tablicamapy[y-1][x] == q)
    {
        tab[0] = x ;
        tab[1] = y-1;
        if (i == 0) {
            return;
        }
        else {
            i--;
        }

    }
    if (y + 1 < height && tablicamapy[y + 1][x] == q) {
        tab[0] = x;
        tab[1] = y + 1;
        if (i == 0) {
            return;
        }
        else {
            i--;
        }
    }
    return;
}

int Mapa::IleDrog(int x, int y) {
    return IleJest(x, y, '#');
}
int Mapa::IleMiast(int x, int y) {
    return IleJest(x, y, '*');
}

 int Mapa::IleJest(int x, int y,const char q) {
    if (x < 0 || y < 0) {
        return 0;
    }
    int ret = 0;
    if (x - 1 >= 0 && tablicamapy[y][x-1] == q)
        ret++;
    if (x + 1 < width && tablicamapy[y][x+1] == q)
        ret++;
    if (y - 1 >= 0 && tablicamapy[y-1][x] == q)
        ret++;
    if (y + 1 <height && tablicamapy[y+1][x] == q)
        ret++;
    return ret;
}

void Mapa::Wypisz()
{
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            cout << tablicamapy[i][j];
        }
        cout << endl;
    }
}

void Mapa::Dodaj(int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie)
{
    this->szukanie->Dodaj(xm,ym,x,y,xprev,yprev,dlugosc,rozwidlenie);
}

void Mapa::Usun()
{
}

void Mapa::Szukaj(Zarzadzanie* zarzadznie, int xm, int ym, int x, int y, int xprev, int yprev, int dlugosc, bool rozwidlenie)
{

    int ileMiast = IleMiast(x, y);
    int ileDrog = IleMiast(x, y);
    int tab[2] = { -1,-1 };
    
    if (ileMiast == 0 && ileDrog == 0)
        return;
    else if (ileMiast == 1 && ileDrog == 0) {
        ZnajdzWspoldzedne(x, y, '*', tab);
        zarzadznie->dodajSasiedztwo(xm, ym, tab[0], tab[1], dlugosc + 1);
    }

    //---
    

}
PunktyOdwiedzone::PunktyOdwiedzone(int x, int y) {
    this->x = x;
    this->y = y;
    this->next = NULL;
}

