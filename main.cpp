#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctime>

using namespace std;
const int N = 20; //standard za broj predmeta po semestru (HIPOTETICKI)

void spisak_predmeta(ifstream& Unos, string a[], int& broj_predmeta);
void stres_sedmica(ifstream& Unos, string sedmica[]);
void casovi_sedmica(ifstream& Unos, int a[]);
void prijedlog(string predmeti[], int broj_predmeta, int stres[], int ostatak, string predlozeno[], int& i);
void casovi_predmet(ifstream& Unos, int stres[], int broj_predmeta);


int main()
{
    srand(time(0));
    //////////////////////////////////DOBAVLJANJE PODATAKA/////////////////////////////////
    ifstream Unos;
    string predmeti[N]; //Postavka
    string sedmica[7] = {"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
    int broj_predmeta = 0;

    spisak_predmeta(Unos, predmeti, broj_predmeta);

    cout << "Stres lvl" << endl << endl;
    stres_sedmica(Unos, sedmica);


    ///////////////////////////////////PROCES I ISPIS PODATAKA///////////////////////////////

    ofstream Ispis;

    int odluka;

    cout << "Odaberi dan: " << endl;

    for (int i = 0; i < 7; i++)
    {
        cout << i + 1 << ". " << sedmica[i] << endl;
    }

    cout << endl << "Odluka: ";

    do{
        cin >> odluka;
    }while(odluka < 1 or odluka > 7);
    cout << endl;

    //Odluka nam pomaze da tacno odredimo koji je dan u pitanju

    //podaci o casovima po danu tokom sedmice, redom od pon-ned
    int casovi[7];
    casovi_sedmica(Unos, casovi);

    //podaci o casovima po predmetima tokom sedmice, KLJUCNO za stres faktor
    int stres[broj_predmeta];
    casovi_predmet(Unos, stres, broj_predmeta);

    //Priprema za prijedlog
    int poeni = 10; //poeni tokom dana
    int ostatak = poeni - casovi[odluka - 1]; //odluka - 1 zbog niza
    cout << "OSTATAK: " << ostatak << endl << endl;
    string predlozeno[5] = {"", "", "", "", ""}; //Prazan niz stringova za predlozeno, trebat ce nam za ispis u iskoristeno.txt
    int broj_prijedloga = 0;

    prijedlog(predmeti, broj_predmeta, stres, ostatak, predlozeno, broj_prijedloga); //glavni dio koda

    cout << "PRIJEDLOGA: " << broj_prijedloga << endl << endl; //TEST
    for(int i = 0; i < broj_prijedloga; i++)
        cout << predlozeno[i] << endl;

    //sada pisemo iz predlozeno u iskoristeno.txt, za sljedeci put kada bude korisnik koristio
    Ispis.open("Files/iskoristeno.txt", ios_base::app);
    for(int i = 0; i < broj_prijedloga; i++)
        Ispis << predlozeno[i] << endl;
    Ispis.close();

    return 0;
}


void spisak_predmeta(ifstream& Unos, string a[], int& broj_predmeta)
{
    Unos.open("Files/predmeti.txt");

    //ispise sve predmete
    cout << "Spisak predmeta: " << endl << endl;

    //Spasavamo predmete u niz stringova, radi kasnijeg rada za davanje random predmete za vjezbanje

    while(getline(Unos, a[broj_predmeta]))
        broj_predmeta++;

    Unos.close();


    Unos.open("Files/casova.txt");
    int casovi[N];
    //dovolino je for petlja ovdje, ne trebamo testirati da li je validno zbog programa getPredmete
    for(int i = 0; i < broj_predmeta; i++)
        Unos >> casovi[i];

    for(int i = 0; i < broj_predmeta; i++)
        cout << i + 1 << ". " << a[i] << "/ Jacina: " << casovi[i] << endl;
    cout << endl;

    Unos.close();
}


void casovi_sedmica(ifstream& Unos, int a[])
{
    //funkcija za dobavljanje podataka iz sedmica.txt, tj. podaci o sedmicnoj nastavi po danu
    Unos.open("Files/sedmica.txt");

    for(int i = 0; i < 7; i++)
        Unos >> a[i];

    Unos.close();
}


void casovi_predmet(ifstream& Unos, int stres[], int broj_predmeta)
{
    //funkcija za dobavljanje podataka iz sedmica.txt, tj. podaci o sedmicnoj nastavi po predmetima
    Unos.open("Files/casova.txt");

    for(int i = 0; i < broj_predmeta; i++)
        Unos >> stres[i];

    Unos.close();
}


void prijedlog(string predmeti[], int broj_predmeta, int stres[], int ostatak, string predlozeno[], int& i)
{
    int faktor[broj_predmeta];

    for(int i = 0; i < broj_predmeta; i++) //ovo je za stres faktor (krediti), koliko treba da se nesto pojavi tokom sedmice, kako bi bilo balansirano, uzimamo po broju predavanja
        {
            faktor[i] = stres[i];
        }

    ifstream Unos;
    ofstream Ispis;
    Unos.open("Files/iskoristeno.txt");
    string pom; //ova varijabla ce nam biti pomocna za uporedjivanje

    while(getline(Unos, pom)) //Sada gledamo koliko se sta pojavilo u File-u "iskoristeno.txt"
    {
        for(int i = 0; i < broj_predmeta; i++)
        {
            if(predmeti[i] == pom)
            {
                faktor[i]--; //gledamo koliko je sta iskoristeno i ukoliko se nadje nesto slicno, onda
            }
        }
    }

    Unos.close();

    //postavljanje prijedloga
    while(ostatak > 0)
    {
        //sada provjeravamo da li su sve faktori stresa iskoristeni, pretpostavka je da jesu sve nule u faktor
        bool suNule = true;
        for(int i = 0; i < broj_predmeta; i++)
        {
            if(faktor[i] != 0) //ako nadjemo ijedan nenulti clan, tada nisu sve nule u faktor
                suNule = false;
        }

        //u slucaju da imamo sve nule u faktori
        if(suNule)
        {
            Ispis.open("Files/iskoristeno.txt"); //brisemo sve podatke sa iskoristeno.txt
            Ispis << "";
            Ispis.close();

            for(int i = 0; i < broj_predmeta; i++) //i restartujemo faktore
            {
                faktor[i] = stres[i];
            }
            //TREBA OPTIMIZIRATI OVAJ SISTEM PRIJEDLOGA ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

        int nasumicno = 0;

        do{
            nasumicno = rand() % broj_predmeta; //jedan od broj_predmeta predmeta izaberemo
        }while(faktor[nasumicno] == 0); //sada biramo predmete tako da, ako su vec iskoristeni, da se iskoriste drugi predmeti


        faktor[nasumicno]--; //smanjujemo broj faktora po predmetu
        predlozeno[i] = predmeti[nasumicno];

        i++;
        ostatak -= 2;
    }
}


void stres_sedmica(ifstream& Unos, string sedmica[])
{
    //funkcija za ispis dane u sedmici i casova predavanja i vjezbi

    int casovi[7];
    Unos.open("Files/sedmica.txt");
    for(int i = 0; i < 7; i++)
        Unos >> casovi[i];
    Unos.close();

    for(int i = 0; i < 7; i++)
        cout << sedmica[i] << " : " << casovi[i] << " casova" << endl;
    cout << endl;

}


/*TESTOVI

 for(int i = 0; i < 7; i++) //TEST
        cout << casovi[i] << " ";


    cout << "CASOVI PREDMETI: ";
    for(int i = 0; i < broj_predmeta; i++)
        cout << stres[i] << " ";
    cout << endl << endl;

    for(int i = 0; i < broj_predmeta; i++)
        cout << predmeti[i] << endl;
    //cout << broj_predmeta << endl; //TEST*/



