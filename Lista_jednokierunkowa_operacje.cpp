#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

struct Lista //DEKLARACJA LISTY
{
  int data;
  struct Lista* nastepny;
};

void DodajNaKoniec(struct Lista** poczatek, int nowy) //FUNKCJA DO DODAWANIA NOWYCH ELEMENTOW NA KONIEC LISTY
{
    struct Lista* nowa_Lista = (struct Lista*) malloc(sizeof(struct Lista)); //PRZYDZIELENIE PAMIECI
    struct Lista *ostatni = *poczatek;
    nowa_Lista->data  = nowy;
    nowa_Lista->nastepny = NULL;
    if (*poczatek == NULL) //CZY LISTA PUSTA
    {
       *poczatek = nowa_Lista;
       return;
    }
    while (ostatni->nastepny != NULL)
    {
       ostatni = ostatni->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
    }
    ostatni->nastepny = nowa_Lista;
    return;
}

int LosowanieLiczb(int a, int b) //prosty generator liczb losowych z przedzialu a do b (a musi byc mniejsze od b)
{
int losowa;

	if(a<b)
	{
    	losowa = (rand() % (b - a + 1)) + a; //GENEROWANIE LICZB Z ZAKRESU
	}
	
	return losowa;
}

void wypisz_Liste(struct Lista* Lista)
{
	int licznik = 1;
    while (Lista != NULL)// DO MOMENTU KIEDY LISTA NIE BEDZIE NULLEM (NULL - PUSTA) WYPISZE WSZYSKIE ELEMENTY
    {
        printf("%d ", Lista->data);
        if(licznik%10==0)
        {
        	printf("\n"); //IF ZEBY WYPISAC PO 10 ZNAKOW
		}
        Lista = Lista->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
        licznik++;
    }
    printf("\n");
}

long long int sumaLista(struct Lista* poczatek) //FUNKCJA ZLICZAJACA SUME ELEMENTOW Z LISTY
{
    struct Lista* licz = poczatek; //DEKLARACJA POCZATKU
    int suma = 0;
    while (licz != NULL)
        {
        suma += licz->data; //SUMOWANIE KOLEJNYCH ELEMENTOW
        licz = licz->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
        }
    return suma;
}

long long int wielkosc_Listy(Lista* poczatek) //FUNCKJA SLUZACA DO ZLICZENIA WIELKOSCI LISTY
{
    int licznik = 0;

    Lista* obecny_element = poczatek;
    while (obecny_element != NULL) // PRZEGLADANIE WSZYSTKICH ELEMENTOW AZ DO PUSTEGO ZNAKU
    {
        licznik++; //ZMIENNA LICZACA ILOSC WYSTEPOWAN W LISCIE
        obecny_element = obecny_element->nastepny; //PRZEJSCIE DO NASTEPNEGO ELEMENTU
    }
    return licznik; //liczba rowna sie wielkosci tablicy
}

void usunLista(struct Lista* slowo) //FUNCKJA DO USUWANIA DANEGO ELEMENTU
{
    slowo->data = slowo->nastepny->data;
    struct Lista* temp = slowo->nastepny;
    slowo->nastepny = slowo->nastepny->nastepny;
    free(temp);
}

void usunNIEPARZLista(Lista** poczatek) //FUNKCJA DO USUWANIE NIEPARZYSTYCH LICZB Z LISTY
{
    Lista* licz = *poczatek;
    Lista* poprzedni;

    while (licz != NULL && licz->nastepny != NULL)
    {
        if (licz->data % 2 != 0)
        {
            usunLista(licz); //LICZBA NIEPARZYSTA, OZNACZA USUNIECIE JEJ
        }
        else
        {
            poprzedni = licz;
            licz = licz->nastepny;
        }
    }
    if (licz == *poczatek && licz->data % 2 != 0)
        {
        *poczatek = NULL;
        }
    else if (licz->data % 2 != 0)
        {
        poprzedni->nastepny = NULL;
        delete licz;
        }
}

int main()
{
    cout << "WCY21IX4S0 PAWEL MIKSIEWICZ ZADANIE 1 LAB 02" << endl << endl;

    srand(time(0));

    struct Lista* dana = NULL; //poczatek listy bedzie pustym znakiem
    int data;
    int a = 1;
    int b = 100;
    int n = 100;
    int i;

    //1 - WYPELNIENIE LOSOWYMI LICZBAMI Z PRZEDZIAKU 1-100
    for(i=0;i<n;i++)
    {
    data = LosowanieLiczb(a,b);
    DodajNaKoniec(&dana, data);
    }
    //2 - WYSWIETLENIE ZAWARTOSCI LISTY
    wypisz_Liste(dana);
    //3 - OBLICZENIE I WYSWIETLENIE SREDNIEJ Z WARTOSCI UMIESZCZONYCH W LISCIE
    float z1 = sumaLista(dana);
    float v1 = wielkosc_Listy(dana);
    float srednia1 = z1/v1;
    cout << "WYNIK SREDNIEJ WARTOSCI = " << srednia1 << endl << endl;
    //4 - USUNIECIE LICZB NIEPARZYSTYCH
    usunNIEPARZLista(&dana);
    //5 - WYSWIETLENIE LISTY
    wypisz_Liste(dana);
    //6 - OBLICZENIE I WYSWIETLENIE SREDNIEJ Z WARTOSCI UMIESZCZONYCH W LISCIE
    float z2 = sumaLista(dana);
    float v2 = wielkosc_Listy(dana);
    float srednia2 = z2/v2;
    cout << endl << "WYNIK NOWEJ SREDNIEJ WARTOSCI = " << srednia2 << endl;

    return 0;
}
