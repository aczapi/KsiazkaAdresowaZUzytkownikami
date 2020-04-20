#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

string nazwaPlikuKontaktow = "KsiazkaAdresowa.txt";
string nazwaPlikuUzytkownik = "ListaUzytkownikow.txt";
string nazwaPlikuTymczasowego = nazwaPlikuKontaktow + "Tymczasowa.txt";

struct Uzytkownik
{
    int id = 0;
    string nazwa, haslo;
};
struct Kontakt
{
    int id = 0;
    string imie = "", nazwisko = "", nrTelefonu = "", email = "", adresZamieszkania = "";
};
char pobierzZnak()
{
    string wejscie = "";
    char znak  = {0};

    while (true)
    {
        getline(cin, wejscie);

        if (wejscie.length() == 1)
        {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}
string pobierzLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}
string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}
int wczytajLiczbeCalkowita()
{
    string wejscie = "";
    int liczba = 0;

    while (true)
    {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}
string konwerjsaIntNaString(int liczba)
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}
string wyswietlPodaneHasloJakoGwiazdki()
{
    string haslo = "";
    char c;
    int liczbaGwiazdek = 0;
    int gwiazdki;

    while (c != 13)
    {
        c = (char)getch();
        if(c == 13)
        {
            break;
        }
        if(c == 8)
        {
            haslo = haslo.substr(0, haslo.length() -1);
            liczbaGwiazdek--;
            gwiazdki = liczbaGwiazdek;
            system("cls");
            while (gwiazdki > 0)
            {
                cout << "*";
                gwiazdki--;
            }
        }
        else
        {
            liczbaGwiazdek++;
            haslo += c;
            cout << "*";
        }
    }

    return haslo;
}

void zakonczProgram()
{
    cout << endl << "Koniec programu. Do zobaczenia! :)" << endl;
    exit(0);
}
bool sprawdzCzyIstnieje(vector<Kontakt> &kontakty, int idDoZmiany )
{
    system("cls");

    bool istnieje = false;
    for (int i = 0; i < kontakty.size(); i++)
    {
        if(kontakty[i].id == idDoZmiany)
            istnieje = true;
    }

    return istnieje;
}
Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami)
{
    Uzytkownik uzytkownik;

    char znakDzielacy = '|';
    istringstream podzial(daneUzytkownikaOddzielonePionowymiKreskami);
    vector<string> podzieloneDaneUzytkownika;
    for (string daneOsobno; getline(podzial, daneOsobno, znakDzielacy); podzieloneDaneUzytkownika.push_back(daneOsobno));

    uzytkownik.id = atoi(podzieloneDaneUzytkownika[0].c_str());
    uzytkownik.nazwa = podzieloneDaneUzytkownika[1];
    uzytkownik.haslo = podzieloneDaneUzytkownika[2];

    return uzytkownik;
}
int wczytajUzytkownikowZPlikuTekstowego(vector<Uzytkownik> &uzytkownicy)
{
    system("cls");

    Uzytkownik uzytkownik;
    int iloscKontaktow = uzytkownicy.size();
    string daneUzytkownikaOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open (nazwaPlikuUzytkownik.c_str(), ios::in );
    if(plikTekstowy.good() == true)
    {
        while(getline(plikTekstowy, daneUzytkownikaOddzielonePionowymiKreskami))
        {
            uzytkownik = pobierzDaneUzytkownika(daneUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}
void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuUzytkownik.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << uzytkownik.id << '|';
        plikTekstowy << uzytkownik.nazwa << '|';
        plikTekstowy << uzytkownik.haslo << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Konto zostalo utworzone" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
int rejestracja(vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik uzytkownik;

    uzytkownik.id = uzytkownicy.size()+1;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> uzytkownik.nazwa;

    int i=0;
    while(i<uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == uzytkownik.nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> uzytkownik.nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    uzytkownik.haslo = wyswietlPodaneHasloJakoGwiazdki();

    uzytkownicy.push_back(uzytkownik);

    dopiszUzytkownikaDoPliku(uzytkownik);

    return uzytkownik.id;
}

int logowanie (vector<Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    cout << "Podaj login: ";
    cin >> nazwa;
    int i=0;
    while(i<uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for( int proby=0; proby<3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby <<": ";
                haslo = wyswietlPodaneHasloJakoGwiazdki();
                cout << endl;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie" <<endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout <<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout <<"Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}
void zapiszWszystkichUzytkownikowDoPlikuTekstowego(vector<Uzytkownik> &uzytkownicy)
{
    fstream plikTekstowy;
    string liniaZDanymiUzytkownika = "";

    plikTekstowy.open(nazwaPlikuUzytkownik.c_str(), ios::out);
    if (plikTekstowy.good())
    {
        for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
        {
            liniaZDanymiUzytkownika += konwerjsaIntNaString(itr->id) + '|';
            liniaZDanymiUzytkownika += itr->nazwa + '|';
            liniaZDanymiUzytkownika += itr->haslo + '|';

            plikTekstowy << liniaZDanymiUzytkownika << endl;
            liniaZDanymiUzytkownika = "";
        }
        plikTekstowy.close();
    }
    else
    {
        cout << "Nie mozna otworzyc pliku " << nazwaPlikuKontaktow << endl;
    }
}
void zmianaHasla(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string stareHaslo = "", haslo = "";
    Uzytkownik uzytkownik;

    cout <<">>> Zmiana hasla <<<" << endl;

    cout <<"Podaj stare haslo: " << endl;
    stareHaslo = wyswietlPodaneHasloJakoGwiazdki();
    cout << endl;
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++)
    {
        if (itr->id == idZalogowanegoUzytkownika)
        {
            if (itr->haslo == stareHaslo)
            {

                cout <<"Podaj nowe haslo: ";
                itr ->haslo = wyswietlPodaneHasloJakoGwiazdki();
                cout << endl << "Haslo zostalo zmienione" << endl;
                cout << endl;
                Sleep(1500);

            }
            else
            {
                cout << "Podane haslo jest niepoprawne. Nie mozna nadac nowego hasla. Sprobuj ponownie" << endl;
                system("pause");
            }
        }
    }
    zapiszWszystkichUzytkownikowDoPlikuTekstowego(uzytkownicy);
}
void pobierzDaneKontaktu(vector<Kontakt> &kontakty, string daneKontaktuOddzielonePionowymiKreskami, int idUzytkownika)
{
    Kontakt osoba;
    Uzytkownik uzytkownik;

    char znakDzielacy = '|';
    istringstream podzial(daneKontaktuOddzielonePionowymiKreskami);
    vector<string> podzieloneDaneKontaktu;
    for (string daneOsobno; getline(podzial, daneOsobno, znakDzielacy); podzieloneDaneKontaktu.push_back(daneOsobno));

    uzytkownik.id = atoi(podzieloneDaneKontaktu[1].c_str());
    if (uzytkownik.id == idUzytkownika)
    {
        osoba.id = atoi(podzieloneDaneKontaktu[0].c_str());
        osoba.imie = podzieloneDaneKontaktu[2];
        osoba.nazwisko = podzieloneDaneKontaktu[3];
        osoba.nrTelefonu = podzieloneDaneKontaktu[4];
        osoba.email = podzieloneDaneKontaktu[5];
        osoba.adresZamieszkania = podzieloneDaneKontaktu[6];
        kontakty.push_back(osoba);
    }
}
void wczytajDaneKontaktowZPlikuTekstowego(vector<Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    system("cls");
    int iloscKontaktow = 0;

    Kontakt osoba;
    string daneKontaktuOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open (nazwaPlikuKontaktow.c_str(), ios::in );
    if(plikTekstowy.good() == true)
    {
        if(ifstream(nazwaPlikuKontaktow.c_str(), ios::ate).tellg())
        {
            while(getline(plikTekstowy, daneKontaktuOddzielonePionowymiKreskami))
            {
                pobierzDaneKontaktu(kontakty, daneKontaktuOddzielonePionowymiKreskami, idZalogowanegoUzytkownika);

            }
            plikTekstowy.close();
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta. Dodaj kontakt " << endl;
        Sleep(1500);
    }
}
int pobierzId(string daneOddzielonePionowymiKreskami)
{
    int id;

    char znakDzielacy = '|';
    istringstream podzial(daneOddzielonePionowymiKreskami);
    vector<string> podzieloneDane;
    for (string daneOsobno; getline(podzial, daneOsobno, znakDzielacy); podzieloneDane.push_back(daneOsobno));

    id = atoi(podzieloneDane[0].c_str());

    return id;
}

int sprawdzIdOstatniegoKontaktu(vector<Kontakt> kontakty)
{
    system("cls");
    int idOstatniegoKontaktu = 0;

    Kontakt osoba;
    string daneKontaktuOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open (nazwaPlikuKontaktow.c_str(), ios::in );
    if(plikTekstowy.good() == true)
    {
        while(getline(plikTekstowy, daneKontaktuOddzielonePionowymiKreskami))
        {
            idOstatniegoKontaktu = pobierzId(daneKontaktuOddzielonePionowymiKreskami);
        }
        plikTekstowy.close();
    }
    return idOstatniegoKontaktu;
}
void dopiszKontaktDoPliku(Kontakt osoba, int idZalogowanegoUzytkownika)
{
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuKontaktow.c_str(), ios::out | ios::app);

    if (plikTekstowy.good() == true)
    {
        plikTekstowy << osoba.id << '|';
        plikTekstowy << idZalogowanegoUzytkownika << '|';
        plikTekstowy << osoba.imie << '|';
        plikTekstowy << osoba.nazwisko << '|';
        plikTekstowy << osoba.nrTelefonu << '|';
        plikTekstowy << osoba.email << '|';
        plikTekstowy << osoba.adresZamieszkania << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Kontakt zostal dodany" << endl;
        Sleep(1500);
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void utworzNowyKontakt( vector<Kontakt> &kontakty, int idOstatniegoKontaktu, int &idZalogowanegoUzytkownika)
{
    system("cls");
    string imie,nazwisko, nrTelefonu, email, adresZamieszkania;

    Kontakt osoba;
    Uzytkownik uzytkownik;

    cout << ">>> Dodawanie nowego kontaktu <<<" << endl << endl;

    osoba.id = idOstatniegoKontaktu+1;
    cout << "Podaj imie: ";
    osoba.imie = pobierzLinie();
    osoba.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.imie);
    cout << "Podaj nazwisko: ";
    osoba.nazwisko = pobierzLinie();
    osoba.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.nazwisko);
    cout << "Podaj numer telefonu: ";
    cin.sync();
    osoba.nrTelefonu = pobierzLinie();
    cout << "Podaj adres email: ";
    osoba.email = pobierzLinie();
    cout << "Podaj adres zamieszkania: ";
    cin.sync();
    osoba.adresZamieszkania = pobierzLinie();

    kontakty.push_back(osoba);
    dopiszKontaktDoPliku(osoba, idZalogowanegoUzytkownika);
}
void wyswietlListeKontaktow(vector<Kontakt> &kontakty)
{
    system("cls");
    if (!kontakty.empty())
    {
        cout << ">>>Lista kontaktow: <<<" << endl;
        cout << endl;

        for (vector<Kontakt>::iterator  itr = kontakty.begin(); itr != kontakty.end(); itr++)
        {
            cout << "Id:                    " << itr->id << endl;
            cout << "Imie:                  " << itr->imie << endl;
            cout << "Nazwisko:              " << itr->nazwisko << endl;
            cout << "Numer Telefonu:        " << itr->nrTelefonu << endl;
            cout << "Adres Email:           " << itr->email << endl;
            cout << "Adres Zamieszkania:    " << itr->adresZamieszkania << endl;
            cout << endl;
        }

    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void wyszukajKontaktPoImieniu(vector<Kontakt> &kontakty)
{
    system("cls");
    string imieSzukanegoKontaktu = "";
    int iloscKontaktow = 0;

    if (!kontakty.empty())
    {
        cout << ">>>Wyszukiwanie kontaktow o imieniu <<<" << endl << endl;
        cout << "Podaj imie kontaktu, ktorego szukasz: ";
        cin >> imieSzukanegoKontaktu;
        imieSzukanegoKontaktu = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imieSzukanegoKontaktu);

        for (vector<Kontakt>::iterator  itr = kontakty.begin(); itr != kontakty.end(); itr++)
        {
            if (itr->imie == imieSzukanegoKontaktu)
            {
                cout << endl;
                cout << "Id:                    " << itr->id << endl;
                cout << "Imie:                  " << itr->imie << endl;
                cout << "Nazwisko:              " << itr->nazwisko << endl;
                cout << "Numer Telefonu:        " << itr->nrTelefonu << endl;
                cout << "Adres Email:           " << itr->email << endl;
                cout << "Adres Zamieszkania:    " << itr->adresZamieszkania << endl;
                iloscKontaktow++;
            }
        }
        if (iloscKontaktow == 0)
        {
            cout << endl << "Brak kontaktow z tym imieniem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc kontaktow z imieniem: >>> " << imieSzukanegoKontaktu << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscKontaktow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << "Nacisnij 'Enter' aby powrocic do menu glownego";
    getchar();
    getchar();
}
void wyszukajKontaktPoNazwisku(vector<Kontakt> &kontakty)
{
    system("cls");
    string nazwiskoSzukanegoKontaktu = "";
    int iloscKontaktow = 0;

    if (!kontakty.empty())
    {
        cout << ">>>Wyszukiwanie kontaktow o nazwisku <<<" << endl << endl;
        cout << "Podaj nazwisko kontaktu, ktorego szukasz: ";
        cin >> nazwiskoSzukanegoKontaktu;
        nazwiskoSzukanegoKontaktu = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoSzukanegoKontaktu);

        for (vector<Kontakt>::iterator  itr = kontakty.begin(); itr != kontakty.end(); itr++)
        {
            if (itr->nazwisko == nazwiskoSzukanegoKontaktu)
            {
                cout << endl;
                cout << "Id:                    " << itr->id << endl;
                cout << "Imie:                  " << itr->imie << endl;
                cout << "Nazwisko:              " << itr->nazwisko << endl;
                cout << "Numer Telefonu:        " << itr->nrTelefonu << endl;
                cout << "Adres Email:           " << itr->email << endl;
                cout << "Adres Zamieszkania:    " << itr->adresZamieszkania << endl;
                iloscKontaktow++;
            }
        }
        if (iloscKontaktow == 0)
        {
            cout << endl << "Brak kontaktow z tym nazwiskiem w ksiazce adresowej" << endl;
        }
        else
        {
            cout << endl << "Ilosc kontaktow z nazwiskiem: >>> " << nazwiskoSzukanegoKontaktu << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscKontaktow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << "Nacisnij 'Enter' aby powrocic do menu glownego";
    getchar();
    getchar();
}

Kontakt pobierzDaneKontaktu(string daneKontaktuOddzielonePionowymiKreskami)
{
    Kontakt osoba;

    char znakDzielacy = '|';
    istringstream podzial(daneKontaktuOddzielonePionowymiKreskami);
    vector<string> podzieloneDaneKontaktu;
    for (string daneOsobno; getline(podzial, daneOsobno, znakDzielacy); podzieloneDaneKontaktu.push_back(daneOsobno));

    osoba.id = atoi(podzieloneDaneKontaktu[0].c_str());
    osoba.imie = podzieloneDaneKontaktu[2];
    osoba.nazwisko = podzieloneDaneKontaktu[3];
    osoba.nrTelefonu = podzieloneDaneKontaktu[4];
    osoba.email = podzieloneDaneKontaktu[5];
    osoba.adresZamieszkania = podzieloneDaneKontaktu[6];

    return osoba;
}

int pobierzIdUzytkownika(string daneKontaktuOddzielonePionowymiKreskami)
{
    Uzytkownik uzytkownik;

    char znakDzielacy = '|';
    istringstream podzial(daneKontaktuOddzielonePionowymiKreskami);
    vector<string> podzieloneDaneKontaktu;
    for (string daneOsobno; getline(podzial, daneOsobno, znakDzielacy); podzieloneDaneKontaktu.push_back(daneOsobno));

    uzytkownik.id = atoi(podzieloneDaneKontaktu[1].c_str());

    return uzytkownik.id;
}

void edytujKontakt(vector<Kontakt> &kontakty, int idZalogowanegoUzytkownika)
{
    system("cls");
    string imie, nazwisko;
    int idKontaktuDoEdycji = 0;
    int idKontaktuZPliku;
    string daneKontaktuOddzielonePionowymiKreskami = "";

    Kontakt osoba;
    Uzytkownik uzytkownik;
    char wybor;

    cout << ">>> Edycja wybranego kontaktu <<<" << endl << endl;
    cout << "Podaj numer ID kontaktu, ktorego dane chcesz zmienic: ";
    idKontaktuDoEdycji = wczytajLiczbeCalkowita();
    if(sprawdzCzyIstnieje(kontakty,idKontaktuDoEdycji) == true)
    {
        system("cls");
        cout << endl << "Edytuj: " << endl;
        cout << "1 - imie" << endl;
        cout << "2 - nazwisko" << endl;
        cout << "3 - numer telefonu" << endl;
        cout << "4 - email" << endl;
        cout << "5 - adres zamieszkania" << endl;
        cout << "6 - Powrot do menu glownego " << endl;
        cout << endl << "Wybierz 1-6: ";
        cin.sync();
        wybor = pobierzZnak();
        cout << endl << endl;


        fstream plikTekstowy, tymczasowyPlikTekstowy;
        plikTekstowy.open (nazwaPlikuKontaktow.c_str(), ios::in );
        if(plikTekstowy.good() == true)
        {
            tymczasowyPlikTekstowy.open (nazwaPlikuTymczasowego.c_str(), ios::out | ios::app );

            while(getline(plikTekstowy, daneKontaktuOddzielonePionowymiKreskami))
            {
                idKontaktuZPliku = pobierzId(daneKontaktuOddzielonePionowymiKreskami);

                if (idKontaktuDoEdycji != idKontaktuZPliku)
                {
                    uzytkownik.id = pobierzIdUzytkownika(daneKontaktuOddzielonePionowymiKreskami);
                    osoba = pobierzDaneKontaktu(daneKontaktuOddzielonePionowymiKreskami);

                    tymczasowyPlikTekstowy << osoba.id << '|';
                    tymczasowyPlikTekstowy << uzytkownik.id << '|';
                    tymczasowyPlikTekstowy << osoba.imie << '|';
                    tymczasowyPlikTekstowy << osoba.nazwisko << '|';
                    tymczasowyPlikTekstowy << osoba.nrTelefonu << '|';
                    tymczasowyPlikTekstowy << osoba.email << '|';
                    tymczasowyPlikTekstowy << osoba.adresZamieszkania << '|' << endl;

                }
                else
                {
                    osoba = pobierzDaneKontaktu(daneKontaktuOddzielonePionowymiKreskami);

                    switch (wybor)
                    {
                    case '1':
                        cout << "Podaj nowe imie: ";
                        osoba.imie = pobierzLinie();
                        osoba.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.imie);
                        cout << endl << "Imie zostalo zmienione" << endl << endl;
                        Sleep (1500);
                        break;
                    case '2':
                        cout << "Podaj nowe nazwisko: ";
                        osoba.nazwisko = pobierzLinie();
                        osoba.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(osoba.nazwisko);
                        cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
                        Sleep (1500);
                        break;
                    case '3':
                        cout << "Podaj nowy numer telefonu: ";
                        osoba.nrTelefonu = pobierzLinie();
                        cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                        Sleep (1500);
                        break;
                    case '4':
                        cout << "Podaj nowy email: ";
                        osoba.email = pobierzLinie();
                        cout << endl << "Email zostal zmieniony" << endl << endl;
                        Sleep (1500);
                        break;
                    case '5':
                        cout << "Podaj nowy adres zamieszkania: ";
                        osoba.adresZamieszkania = pobierzLinie();
                        cout << endl << "Adres zostal zmieniony" << endl << endl;
                        Sleep (1500);
                        break;
                    case '6':
                        cout << endl << "Powrot do menu glownego" << endl << endl;
                        Sleep (1500);
                        break;
                    default:
                        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                        Sleep (1500);
                        break;
                    }

                    tymczasowyPlikTekstowy << osoba.id << '|';
                    tymczasowyPlikTekstowy << idZalogowanegoUzytkownika << '|';
                    tymczasowyPlikTekstowy << osoba.imie << '|';
                    tymczasowyPlikTekstowy << osoba.nazwisko << '|';
                    tymczasowyPlikTekstowy << osoba.nrTelefonu << '|';
                    tymczasowyPlikTekstowy << osoba.email << '|';
                    tymczasowyPlikTekstowy << osoba.adresZamieszkania << '|' << endl;
                }
            }
        }

        tymczasowyPlikTekstowy.close();
        plikTekstowy.close();


        remove(nazwaPlikuKontaktow.c_str());
        rename(nazwaPlikuTymczasowego.c_str(), nazwaPlikuKontaktow.c_str());
    }
    else
    {
        cout << endl << "Kontakt nie istnieje!Sprobuj ponownie." << endl << endl;
        system("pause");
    }

}

void usunKontakt(vector<Kontakt> &kontakty, int idOstatniegoKontaktu)
{
    char potwierdzenie = 't';

    int idKontaktuDoUsuniecia = 0;
    int idKontaktuZPliku = 0;
    string daneKontaktuOddzielonePionowymiKreskami = "";

    Kontakt osoba;
    Uzytkownik uzytkownik;
    system("cls");


    cout << ">>> Usuwanie wybranego kontaktu <<<" << endl << endl;
    cout << "Podaj numer ID kontaktu, ktorego chcesz usunac: ";
    idKontaktuDoUsuniecia = wczytajLiczbeCalkowita();
    if(sprawdzCzyIstnieje(kontakty,idKontaktuDoUsuniecia) == true)
    {

        cout << "Czy na pewno chcesz usunac kontakt? Nacisnij klawisz <t>, aby potwierdzic." << endl;
        cin >> potwierdzenie;

        if (potwierdzenie == 't')
        {
            fstream plikTekstowy, tymczasowyPlikTekstowy;
            plikTekstowy.open (nazwaPlikuKontaktow.c_str(), ios::in );
            if(plikTekstowy.good() == true)
            {
                tymczasowyPlikTekstowy.open(nazwaPlikuTymczasowego.c_str(), ios::out | ios::app );

                while(getline(plikTekstowy, daneKontaktuOddzielonePionowymiKreskami))
                {
                    idKontaktuZPliku = pobierzId(daneKontaktuOddzielonePionowymiKreskami);
                    if (idKontaktuDoUsuniecia != idKontaktuZPliku)
                    {
                        uzytkownik.id = pobierzIdUzytkownika(daneKontaktuOddzielonePionowymiKreskami);
                        osoba = pobierzDaneKontaktu(daneKontaktuOddzielonePionowymiKreskami);
                        tymczasowyPlikTekstowy << osoba.id << '|';
                        tymczasowyPlikTekstowy << uzytkownik.id << '|';
                        tymczasowyPlikTekstowy << osoba.imie << '|';
                        tymczasowyPlikTekstowy << osoba.nazwisko << '|';
                        tymczasowyPlikTekstowy << osoba.nrTelefonu << '|';
                        tymczasowyPlikTekstowy << osoba.email << '|';
                        tymczasowyPlikTekstowy << osoba.adresZamieszkania << '|' << endl;
                    }
                }
                tymczasowyPlikTekstowy.close();
                plikTekstowy.close();

                cout << "Kontakt zostal usuniety." << endl;
                Sleep(1500);

                remove(nazwaPlikuKontaktow.c_str());
                rename(nazwaPlikuTymczasowego.c_str(), nazwaPlikuKontaktow.c_str());
            }
            else
            {
                cout << "Nie mozna otworzyc pliku: ksiazka_adresowa.txt" << endl;
            }
        }
        else
        {
            cout << "Kontakt nie zostal usuniety. Nastapi powrot do menu glownego" <<endl;
            Sleep(1500);
        }
    }
    else
    {
        cout << "Kontakt nie istnieje!Sprobuj ponownie." << endl;
        Sleep(1500);
    }
}

int main()
{
    vector<Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    vector<Kontakt> kontakty;
    int idOstatniegoKontaktu = 0;

    char wybor;

    wczytajUzytkownikowZPlikuTekstowego(uzytkownicy);

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << ">>> Jesli jestes nowym uzytkownikiem zarejestruj sie. Masz konto? Zaloguj sie :) <<<" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cin.sync();
            wybor = pobierzZnak();

            switch(wybor)
            {
            case '1':
                iloscUzytkownikow = rejestracja(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                break;
            case '9':
                zakonczProgram();
                break;
            }
        }
        else
        {
            system("cls");
            cout << ">>> Ksiazka adresowa <<<" << endl << endl;
            cout << "1. Dodaj nowy kontakt" << endl;
            cout << "2. Wyswietl po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkie kontakty" << endl;
            cout << "5. Usun kontakt" << endl;
            cout << "6. Edytuj kontakt" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "Twoj wybor: " << endl;
            cin.sync();
            wybor = pobierzZnak();
            cout << endl << endl;

            kontakty.clear();
            idOstatniegoKontaktu = sprawdzIdOstatniegoKontaktu(kontakty);
            wczytajDaneKontaktowZPlikuTekstowego(kontakty, idZalogowanegoUzytkownika);

            switch(wybor)
            {
            case '1':
                utworzNowyKontakt(kontakty, idOstatniegoKontaktu, idZalogowanegoUzytkownika);
                break;
            case '2':
                wyszukajKontaktPoImieniu(kontakty);
                break;
            case '3':
                wyszukajKontaktPoNazwisku(kontakty);
                break;
            case '4':
                wyswietlListeKontaktow(kontakty);
                break;
            case '5':
                usunKontakt(kontakty, idOstatniegoKontaktu);
                break;
            case '6':
                edytujKontakt(kontakty, idZalogowanegoUzytkownika);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8':
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}
