#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <conio.h>

using namespace std;

//DEKLARACJA LISTY
struct Lista
{
	string nazwisko;
	string imie;
	int telefon;
	struct Lista *nastepny;
	struct Lista *poprzedni;
};

//FUNCKJA NA DODAWANIE DO LISTY, DODAJE NA POCZATEK
void Dodaj_Lista(struct Lista** poczatek, string nazw, string im, int nowy)
{
    struct Lista* nowa_lista = new Lista;
    nowa_lista->nazwisko = nazw;
    nowa_lista->imie = im;
    nowa_lista->telefon = nowy;
    nowa_lista->nastepny = (*poczatek);
    nowa_lista->poprzedni = NULL;

    if((*poczatek)!=NULL)
    {
    	(*poczatek)->poprzedni = nowa_lista;
	}
    (*poczatek) = nowa_lista;
}

//FUNKCJA NA WYSWIETLANIE LISTY
void Wyswietl_Lista(struct Lista* lista)
{
	struct Lista* ostatni;
    int licznik = 1;
	while(lista != NULL)
	{
	    cout << "Wizytowka nr " << licznik << endl;
	    licznik++;
		cout <<"Nazwisko - " << lista->nazwisko << endl;
		cout <<"Imie - " << lista->imie << endl;
		cout <<"Telefon - " << lista->telefon << endl << endl;
		ostatni = lista;
		lista = lista->nastepny;
	}
}

//FUNKCJA NA SZUKANIE W LISCIE 
int znajdz_w_Liscie(struct Lista* dana, string surname, string name, int podmiot, int index)
{
    struct Lista* obecna = dana;  //inicjacja listy
    if(dana == NULL) // sprawdzenie czy Null
    {
        return -1;
    }
    if(dana->nazwisko == surname && dana->imie == name && dana->telefon == podmiot) //sprawdzenie czy dana jest obecnym elementem listy
    {
    	return index;
    }
    index++;
    return znajdz_w_Liscie(dana->nastepny,surname, name, podmiot, index); //rekurencja
}

//FUNCKJA NA USUWANIE LISTY
void usun_z_Listy(struct Lista** poczatek, int klucz)
{
    struct Lista *nc = *poczatek, *poprzedni; // nc oznacza "na chwile", inaczej obecny sprawdzany element
    if (nc != NULL && nc->telefon == klucz)
    {
        *poczatek = nc->nastepny;
        free(nc); //zwolnienie zmiennej
        return;
    }
    while (nc != NULL && nc->telefon != klucz)
    {
        poprzedni = nc;
        nc = nc->nastepny;
    }
    if (nc == NULL)
    {
        return;
    }
    poprzedni->nastepny = nc->nastepny;

    free(nc); //zwolnienie zmiennej
}

//FUNKCJA NA ZAPISYWANIE DO PLIKU
void Zapisz(struct Lista *w, char nazwapliku[50])
{
    struct Lista *wsk = w;
    ofstream  plik;
    plik.open(nazwapliku);
    if(plik.good() == true) //SPRAWDZENIE CZY PLIK UTWORZONO
	{
        while (wsk != NULL)
		{
			//ZAPISYWANIE DANYCH
            plik << wsk->nazwisko << endl;
			plik << wsk->imie << endl;
			plik << wsk->telefon << endl;
			plik << endl;
            wsk = wsk->nastepny;
        }
    }
    plik.close(); //ZAMKNIECIE PLIKU
}

//SORT OD A - Z WG NAZWISK, SORTOWANIE BABELKOWE
void SortujAZ(struct Lista *start)
{
    int swapped, i;
    struct Lista *sort1;
    struct Lista *sort2 = NULL;

    do
    {
        swapped = 0;
        sort1 = start;
        while (sort1->nastepny != sort2)
        {
            if (sort1->nazwisko > sort1->nastepny->nazwisko)
            {
                swap(sort1->nazwisko, sort1->nastepny->nazwisko);
                swap(sort1->imie, sort1->nastepny->imie);
                swap(sort1->telefon, sort1->nastepny->telefon);
                swapped = 1;
            }
            sort1 = sort1->nastepny;
        }
        sort2 = sort1;
    }
    while (swapped);
}

//SORT OD Z - A WG NAZWISK, SORTOWANIE BABELKOWE
void SortujZA(struct Lista *start)
{
    int zmien, i;
    struct Lista *sort1;
    struct Lista *sort2 = NULL;

    do
    {
        zmien = 0;
        sort1 = start;
        while (sort1->nastepny != sort2)
        {
            if (sort1->nazwisko < sort1->nastepny->nazwisko)
            {
                swap(sort1->nazwisko, sort1->nastepny->nazwisko);
                swap(sort1->imie, sort1->nastepny->imie);
                swap(sort1->telefon, sort1->nastepny->telefon);
                zmien = 1;
            }
            sort1 = sort1->nastepny;
        }
        sort2 = sort1;
    }
    while (zmien);
}

int main()
{
	int telefon, index;
	string surname, name;
	char wybor;
	char nazwapliku[50];

    struct Lista* dana = NULL; //poczatek listy bedzie pustym znakiem

while (1)
{
		system("cls"); //CZYSZCZENIE KONSOLI CMD DLA PRZEJRZYSTSZYCH WYNIKOW

		printf("Operacje na liscie: \n");
		printf("d - Dodaj wizytowke na poczatek \n");
		printf("s - Szukaj wizytowki \n");
		printf("w - Wylistuj elementy listy (A-Z) \n");
		printf("v - Wylistuj elementy listy (Z-A) \n");
		printf("u - Usun wizytowke  \n");
		printf("z - Zapisz do pliku \n");
		printf("k - Koniec dzialania \n");
		printf("Wybierz operacje podajac jej numer (1-5, 0 - koniec dzialania): \n");

		cin >> wybor;

		system("cls"); //CZYSZCZENIE KONSOLI CMD DLA PRZEJRZYSTSZYCH WYNIKOW
        switch(wybor)
        {
		case 'k': //KONIEC PROGRAMU
            {
            	printf("Koniec pracy programu.");
            	exit(0);
                return 0;
            }
            break;

        case 'd': //DODAWANIE DO LISTY
                cout << "1. Nazwisko" << endl;
				cin >> surname;
				cout << "2. Imie" << endl;
				cin >> name;
				cout << "3. Telefon" << endl;
				cin >> telefon;
                Dodaj_Lista(&dana, surname, name, telefon); //wywolanie funkcji
                printf("\n");
				break;

        case 's': //SZUKAJ W LISCIE
        		if(dana == NULL)
                {
                    printf("Brak elementow w liscie \n");
                }
                else
                {
                	cout << "Podaj: " << endl;
                    cout << "1. Nazwisko" << endl;
					cin >> surname;
					cout << "2. Imie" << endl;
					cin >> name;
					cout << "3. Telefon" << endl;
					cin >> telefon;
                    index = znajdz_w_Liscie(dana, surname, name, telefon,0); //wywolanie funkcji
                    if(index == -1)
                    {
                        printf("Nie znaleziono takiej wizytowki o wprowadzonych danych \n");
                    }
                    else
                    {
                        printf("Znaleziono taka wizytowke o wprowadzonych danych \n");
                    }
                }
				printf("\n");
				break;

    	case 'w': //SORTUJ A-Z
				if(dana == NULL)
            	{
                printf("Lista jest pusta. \n");
           		}
            	else
            	{
				printf("Wszystkie wizytowki: \n \n");
    			SortujAZ(dana);
                Wyswietl_Lista(dana);
    			}
    			break;

        case 'v': //SORTUJ Z-A
                if(dana == NULL)
            	{
                printf("Lista jest pusta. \n");
           		}
            	else
            	{
				printf("Wszystkie wizytowki: \n \n");
    			SortujZA(dana);
                Wyswietl_Lista(dana);
    			}
    			break;

    	case 'u': //USUN WSKAZANY ELEMENT
    			if(dana == NULL)    //usuwanie elementu z listy jesli wpisana operacja wynosi 2, ale najpierw sprawdzenie czy wogole mozna cos usunac
                {
                    printf("Nie mozna wykonac operacji poniewaz nie ma elementow w liscie \n");
                }
                else
                {
                    printf("Usun wskazany element: \n");
                    cout << "1. Nazwisko" << endl;
					cin >> surname;
					cout << "2. Imie" << endl;
					cin >> name;
					cout << "3. Telefon" << endl;
					cin >> telefon;
                    index = znajdz_w_Liscie(dana,surname, name, telefon, 0); //wywolanie funkcji
                    if(index == -1)
                    {
                    	printf("Nie znaleziono takiej wizytowki \n");
                    }
                    else
                    {
                        usun_z_Listy(&dana,telefon); //wywolanie funkcji
                        printf("Usunieto pomyslnie wskazana wizytowke \n");
                    }
                }
				printf("\n");
				break;

		case 'z':
				cout << "Podaj nazwe pliku do zapisu wraz z rozszerzeniem(!)." << endl;
				cout <<  "Do pliku wizytowki zostana wstawione alfabetycznie A-Z." << endl;
  				cin >> nazwapliku;
  				SortujAZ(dana);
  				Zapisz(dana,nazwapliku);
  				cout << "Zapisano pomyslnie" << endl;
  				break;
    	default:
    			cout << "Wpisano bledny numer operacji. Sprobuj ponownie." << endl;
    	}
    	system("pause"); //POTWIERDZENIE DOWOLNA AKCJA NA KLAWATIURZE ZEBY PRZEJSC DALEJ
};

return 0;
}

