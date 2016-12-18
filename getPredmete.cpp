#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main()
{
    /////////////////////////////////////////////////SPISAK PREDMETA/////////////////////////////////////////////////////////////
    //Program za unos predmeta i sedmicno njihovih casova

    ofstream Ispis;
    ifstream Upis;

    bool jePrazan = true;

    string test; //pomocna varijabla
    Upis.open("Files/predmeti.txt");

    while(getline(Upis, test)) //Ispitujemo da li je fajl prazan
        jePrazan = false;

    Upis.close();

    //U slucaju da je vec korisnik ovo koristio
    if(!jePrazan)
    {
        cout << "Vec imate upisane predmete! Da li zelite promijeniti predmete?" << endl;
        cout << "Da - 1" << endl << "Ne - 0" << endl;
        cout << "Odluka: ";

        int odluka = 2;

        while(odluka != 1 and odluka != 0)
            cin >> odluka;

        if(odluka == 0)
        {
         cout << "Vasi podaci su ostali nepromijenjeni!" << endl;
         exit(1);
        }
    }

    const int BROJ_PREDMETA = 20;
    string a[BROJ_PREDMETA];
    int broj_casova[BROJ_PREDMETA];


    cout << endl << endl << "Dobrodosli na Recommender!\nUnesite broj predmeta u semestru: ";

    int n;
    do{
        cin >> n; //ovo ce biti za broj predmeta u semestru //Kako napraviti exception handling u C++?

    }while(n < 0 or n > 20);
    getline(cin, test); //ovo je jedno od rjesenja buga (KONSULTACIJE) Kako ovo elegantnije rijesiti (zbog toga sto cin ostavlja \n karakter na kraju naredbe i sljedeci getline hvata prazan string

    //sada hocemo da dobijemo informacije koji su predmeti u pitanju
    cout << endl << "Unesite nazive svih " << n << " predmeta u vasem semestru: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << "Predmet: ";
        getline(cin, a[i]);
        cout << "Koliko sedmicno imate casova za " << a[i] << ": ";
        cin >> broj_casova[i];
        getline(cin, test); //jos jedan bug (isti je u pitanju), (KONSULTACIJE)
        cout << endl;
    }

    cout << endl << endl << endl;
    for(int i = 0; i < n; i++)
        cout << a[i] << " - " << broj_casova[i] << " casova sedmicno" << endl;

    cout << "Vasi predmeti su spaseni u ovakvom formatu!" << endl;

    //spasavanje podataka za predmete u predmeti.txt fajlu
    Ispis.open("Files/predmeti.txt");

    for(int i = 0; i < n; i++)
        Ispis << a[i] << endl;

    cout << endl << endl;
    Ispis.close();

    //spasavanje broj casova u skladu sa predmetima
    Ispis.open("Files/casova.txt");

    for(int i = 0; i < n; i++)
        Ispis << broj_casova[i] << endl;

    Ispis.close();

    ////////////////////////////////////////////////////////SEDMICA///////////////////////////////////////////////////////////////

    Ispis.open("Files/sedmica.txt"); //prvi red - ponedjeljak, drugi red - utorak, ..., nedjelja - 7. red - upisani su brojevi casova
    string sedmica[7] = {"Ponedjeljak", "Utorak", "Srijeda", "Cetvrtak", "Petak", "Subota", "Nedjelja"};
    int predavanja[7];

    for(int i = 0; i < 6; i++)
    {
        cout << "Koliko casova imate u " << sedmica[i] << ": ";
        cin >> predavanja[i];
        Ispis << predavanja[i] << endl;
    }

    Ispis << 0 << endl;

    cout << endl << "Vasi podaci su spremljeni! Mozete sada koristiti program displayVjezbanje za vas radni dan u skladu sa podacima koje ste pruzili!" << endl;
    cout << "Sretno!" << endl;

    Ispis.close();

    return 0;
}
