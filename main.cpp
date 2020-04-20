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

using namespace std;

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

void zakonczProgram()
{
    cout << endl << "Koniec programu. Do zobaczenia! :)" << endl;
    exit(0);
}



int main()
{
    vector<Uzytkownik> uzytkownicy;
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;

    vector<Kontakt> kontakty;
    int idOstatniegoKontaktu = 0;

    char wybor;

   // iloscUzytkownikow = wczytajDaneZPlikuTekstowego(uzytkownicy);

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << ">>> Jesli jestes nowym uzytkownikiem zarejestruj sie. Masz konto? Zaloguj sie :) <<<" << endl << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" <<endl;
            wybor = pobierzZnak();

            switch(wybor)
            {
            case '1':
                //iloscUzytkownikow = rejestracja(uzytkownicy);
                break;
            case '2':
                //idZalogowanegoUzytkownika = logowanie(uzytkownicy);
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
            wybor = pobierzZnak();
            cout << endl << endl;

            //kontakty.clear();
            //idOstatniegoKontaktu = sprawdzIdOstatniegoKontaktu(kontakty);
            //wczytajDaneKontaktowZPlikuTekstowego(kontakty, idZalogowanegoUzytkownika);

            switch(wybor)
            {
            case '1':
                // idOstatniegoKontaktu = utworzNowyKontakt(kontakty, idOstatniegoKontaktu, idZalogowanegoUzytkownika);
                break;
            case '2':
                // wyszukajKontaktPoImieniu(kontakty);
                break;
            case '3':
                // wyszukajKontaktPoNazwisku(kontakty);
                break;
            case '4':
                //  wyswietlListeKontaktow(kontakty);
                break;
            case '5':
                // usunKontakt(kontakty, idOstatniegoKontaktu);
                break;
            case '6':
                // edytujKontakt(kontakty, idZalogowanegoUzytkownika);
                break;
            case '7':
                //  zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8':
                // idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}
