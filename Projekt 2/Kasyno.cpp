#include "Kasyno.h"
#include <windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <codecvt>
#include <time.h>
using namespace std;


Kasyno:: Kasyno() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	Karta k(0, 0);
	int z = 0;
	for (int y = 0; y < 13; y++) {
		k.setWartosc(y);
		for (int x = 0; x < 4; x++) {
			k.setKolor(x);
			talia[z] = k;
			z++;
		}
	}
	tasowanie();
	iloscOddanychKart = 0;
	//wcout << "\naktywacja konstruktor kasyna!";
}
Kasyno::~Kasyno() {
	if (iloscGraczy > 0) {
		for (int i = 0; i < iloscGraczy; i++) {
			if (tablicaGraczy[i] != nullptr) delete tablicaGraczy[i];
		}
		delete[] tablicaGraczy;
	}
	//wcout <<endl<< "destruktor kasyna aktywowany!";
}
void Kasyno::tasowanie() {
	srand(time(NULL));
	Karta temp_karta(0, 0);
	int temp_miejsce;
	int wylosowane_miejsce;

	for (int x = 0; x < 100; x++) {	//tasowanie 100 razy talii
		wylosowane_miejsce = (std::rand() % 52);
		temp_karta = talia[wylosowane_miejsce];
		temp_miejsce = wylosowane_miejsce;

		wylosowane_miejsce = (std::rand() % 52);
		talia[temp_miejsce] = talia[wylosowane_miejsce];
		talia[wylosowane_miejsce] = temp_karta;
	}
}
void Kasyno::pokazKarte(int _ktora) {

	wcout <<endl<< "Figura:" << talia[_ktora].getFigura() << "      Kolor:";
		switch (talia[_ktora].getKolor()) {
			case 3:
			wcout << L"\u2665" << "  ";
			break;
			case 4:
			wcout << L"\u2666" << "  ";
			break;
			case 5:
			wcout << L"\u2663" << "  ";
			break;
			case 6:
			wcout << L"\u2660" << "  ";
			break;
	}
}
void Kasyno::pokazWszystkieKarty() {
	for (int x = 0; x < 52; x++) pokazKarte(x);
}

void Kasyno::graj() {
	wcout << "\nwitaj w kasynie!";
	bool czy_gramy = 1;
	do {
		reset();	//reset do wartosci poczatkowych

		//PODANIE ILOSCI GRACZY LUDZKICH
		wcout << "\npodaj liczbe graczy ludzkich (od 1 do 3): ";	
		int temp_ilosc_graczy_ludzkich = 1;
		do {
			if (temp_ilosc_graczy_ludzkich < 1 || temp_ilosc_graczy_ludzkich > 3) wcout << "\nPodaj poprawna ilosc!";
			cin >> temp_ilosc_graczy_ludzkich;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(5000, '\n');
			}
		} while (temp_ilosc_graczy_ludzkich < 1 || temp_ilosc_graczy_ludzkich > 3);
		//PODANIE ILOSCI BOTOW
		wcout << "\npodaj liczbe botow (od 1 do 3): ";
		int temp_ilosc_botow = 1;
		do {
			if (temp_ilosc_botow < 1 || temp_ilosc_botow > 3) wcout << "\nPodaj poprawna ilosc!";
			cin >> temp_ilosc_botow;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(5000, '\n');
			}
		} while (temp_ilosc_botow < 1 || temp_ilosc_botow > 3);
		//------------------------------------------------------------------------
		//TWORZENIE GRACZY LUDZKICH
		for (int x = 1; x <= temp_ilosc_graczy_ludzkich; x++) {
			wcout << "\nnazwa dla gracza nr." << x << " (max. 20 znakow): ";
			dodajGracza();
			tablicaGraczy[x - 1]->wezKarte(dajKarte());
			tablicaGraczy[x - 1]->wezKarte(dajKarte());
		}
		//TWORZENIE BOTOW
		for (int x = 1; x <= temp_ilosc_botow; x++) {
			wcout << "\nnazwa dla gracza nr." << x << " (max. 20 znakow): ";
			dodajBota();
			tablicaBotow[x - 1]->wezKarte(dajKarte());
			tablicaBotow[x - 1]->wezKarte(dajKarte());
		}
		//-------------------------------------------------------------------------
		//ROZPOCZECIE GRY
		system("cls");
		wcout << "\nCzas zaczac rozgrywke!";
		int ilePass = 0;	//zmienna pomocnicza okreslajaca ile graczy pass
		do {	//petla rozgrywki

			for (int x = 0; x < iloscGraczy; x++) {
				if (tablicaGraczy[x]->zwrocPass() == false) {
					wcout << "\nGracz o nazwie: " << tablicaGraczy[x]->zwroc_nick() << ": " << endl;
					tablicaGraczy[x]->pokazReke();
					tablicaGraczy[x]->czyPass();
					if (tablicaGraczy[x]->zwrocPass() == false) {
						tablicaGraczy[x]->wezKarte(dajKarte());
						tablicaGraczy[x]->pokazReke();
					}
					else ilePass++;
					system("Pause");
					system("cls");
				}
			}
		} while (ilePass != iloscGraczy);

		system("cls");
		znalezenieZwyciezcy();	//sprawdzenie wynikow gry i znalezienie zwyciezcy
		system("Pause");
		system("cls");
		zapisz_wyniki();	//zapisanie wynikow w pliku tekstowym

		//CZY CHCESZ ZAGRAC JESZCZE RAZ?
		wcout << "\nczy chcesz zagrac jeszcze raz? wpisz 1 aby grac dalej, wpisz 0 aby zakonczyc gre: ";
		do {
			cin >> czy_gramy;
			if (czy_gramy < 0 || czy_gramy>1) wcout << "\nPodaj poprawna liczbe!: ";
			cin.clear(); //kasowanie flagi b³êdu strumienia
			cin.ignore(5000, '\n');
		} while (czy_gramy < 0 || czy_gramy>1);
		
		//USUWANIE GRACZY, JEŒLI KONIEC ROZGRYWKI
		if (czy_gramy == 1) {
			usun_graczy();
		}
	} while (czy_gramy == 1);
	
}

Karta* Kasyno::dajKarte() {
	iloscOddanychKart++;
		if (iloscOddanychKart < 52) {
			return &talia[iloscOddanychKart - 1];
		}
		else wcout << "Brak kart, koniec gry!";
}

void Kasyno::dodajGracza()
{	
	if (iloscGraczy == 0) {
		iloscGraczy++;
		tablicaGraczy = new Gracz*[iloscGraczy];
		tablicaGraczy[0] = new Gracz(*this);
	}
	else {
		Gracz **tempTablicaGraczy = new Gracz * [iloscGraczy];
		for (int x = 0; x < iloscGraczy; x++) {
			tempTablicaGraczy[x] = tablicaGraczy[x];
		}
		delete[] tablicaGraczy;
		iloscGraczy++;
		tablicaGraczy = new Gracz*[iloscGraczy];
		for (int x = 0; x < iloscGraczy - 1; x++) {
			tablicaGraczy[x] = tempTablicaGraczy[x];
		}
		tablicaGraczy[iloscGraczy - 1] = new Gracz(*this);
	}
		
}

void Kasyno::dodajBota()
{	
	if (iloscBotow == 0) {
		iloscBotow++;
		tablicaBotow = new Gracz * [iloscBotow];
		tablicaBotow[0] = new Gracz(*this);
	}
	else {
		Gracz** temptablicaBotow = new Gracz * [iloscBotow];
		for (int x = 0; x < iloscBotow; x++) {
			temptablicaBotow[x] = tablicaBotow[x];
		}
		delete[] tablicaBotow;
		iloscBotow++;
		tablicaBotow = new Gracz * [iloscBotow];
		for (int x = 0; x < iloscBotow - 1; x++) {
			tablicaBotow[x] = temptablicaBotow[x];
		}
		tablicaBotow[iloscBotow - 1] = new Gracz(*this);
	}
}

void Kasyno::znalezenieZwyciezcy()
{
	wcout << "\nTABLICA PUNKTOW:";
	for (int x = 0; x < iloscGraczy; x++) {
		wcout << "\nGracz o nazwie: " << tablicaGraczy[x]->zwroc_nick() << "\t\tilosc punktow: " << tablicaGraczy[x]->zwrocPunkty();
	}
	int ilosc_Przegranych = 0;
	int ilosc_Oczek = 0;
	int ilosc_MniejOd22 = 0;	//te osoby, ktore maja mniej niz 21 pkt

	for (int x = 0; x < iloscGraczy; x++) {	//gdy wszyscy przekroczyli 21 pkt
		if (tablicaGraczy[x]->zwrocPunkty() > 21) ilosc_Przegranych++;
		if (tablicaGraczy[x]->zwrocPunkty() == 21) ilosc_Oczek++;
		if (tablicaGraczy[x]->zwrocPunkty() < 22) ilosc_MniejOd22++;
	}
	//wcout << "\n------------------------------------";
	//wcout << "\nilosc_Przegranych=" << ilosc_Przegranych << "\nilosc_oczek=" << ilosc_Oczek << "\nilosc_mniej niz 21pkt=" << ilosc_MniejOd22;
	
		//Przypadek gdy ktos wygral				
	int iloscWygranych = 0;
	if (ilosc_MniejOd22 != 0) {
		for(int x = 0; x < iloscGraczy; x++){
				if(tablicaGraczy[x]->zwrocPunkty()<21) wygrany = tablicaGraczy[x];
		}
		for (int x = 0; x < iloscGraczy; x++) {
			if (wygrany->zwrocPunkty()<tablicaGraczy[x]->zwrocPunkty()&& tablicaGraczy[x]->zwrocPunkty()<22) wygrany= tablicaGraczy[x];
		}
		int zwycieskiePunkty = wygrany->zwrocPunkty();
		for (int x = 0; x < iloscGraczy; x++) {
				if (zwycieskiePunkty == tablicaGraczy[x]->zwrocPunkty()) iloscWygranych++;
		}
		wcout << "\n------------------------------------";
		//wcout << "\nzmienna iloscWygranych: " << iloscWygranych;
		//wcout << "\nzmienna zwycieskiePunkty: " << zwycieskiePunkty;
	}
		
		//WYPISANIE GRACZY WYGRANYCH
		//Gdy mamy jednego wygranego
		if(iloscWygranych==1)
		{
			wcout << "\nWygral gracz:";
			wcout << "\n\nNAZWA" << "\t\t\tILOSC PUNKTOW";
			for (int x = 0; x < iloscGraczy; x++) {
				if (tablicaGraczy[x]->zwrocPunkty() == wygrany->zwrocPunkty())wcout << endl << tablicaGraczy[x]->zwroc_nick() << "\t\t\t" << tablicaGraczy[x]->zwrocPunkty();
			}
			wcout << endl;
		}
		//Gdy mamy wiecej wygranych niz 1
		if (iloscWygranych > 1) {
			wcout << "\nREMIS! Najwieksza ilosc punktow zdobyli:";
			for (int x = 0; x < iloscGraczy; x++) {
				if(tablicaGraczy[x]->zwrocPunkty() == wygrany->zwrocPunkty()) wcout <<endl<< tablicaGraczy[x]->zwroc_nick() << "   ilosc punktow: " << tablicaGraczy[x]->zwrocPunkty();
			}
			wcout << endl;
		} 
		//Gdy nikt nie wygral
		if (ilosc_Przegranych == iloscGraczy) wcout << "\n------------------------------------" << "\nwszyscy przegrali!\n";
}

void Kasyno::usun_graczy()
{
	for (int i = 0; i < iloscGraczy; i++) {
		if (tablicaGraczy[i] != nullptr) delete tablicaGraczy[i];
	}
	delete[] tablicaGraczy;
}

void Kasyno::reset()
{
	Karta k(0, 0);
	int z = 0;
	for (int y = 0; y < 13; y++) {
		k.setWartosc(y);
		for (int x = 0; x < 4; x++) {
			k.setKolor(x);
			talia[z] = k;
			z++;
		}
	}
	tasowanie();
	iloscOddanychKart = 0;
	iloscGraczy = 0;
}

void Kasyno::zapisz_wyniki() {
	int x;
	ofstream plik_z_wynikami;

	do {
		wcout << "Czy chcesz zapisac wyniki na przyszlosc?\n1 - Tak, bardzo chetnie\n2 - Nie, dziekuje" << endl;
		cin >> x;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(5000, '\n');
		}

		switch (x)
		{

		case 1:

			plik_z_wynikami.open("Wyniki_Gry_w_Oczko.txt", ofstream::out);
			plik_z_wynikami << "Wyniki gry w Oczko:\n\nNazwa:\t\tPunkty:\t\tKarty:";
			for (int i = 0; i <	iloscGraczy; i++)
			{
				plik_z_wynikami << std::endl << tablicaGraczy[i]->zwroc_nick() << "\t\t";
				plik_z_wynikami << tablicaGraczy[i]->zwrocPunkty() << "\t\t";
				for (int j = 0; j < tablicaGraczy[i]->zwrocIleKart(); j++)
				{
					switch (tablicaGraczy[i]->zwrocReka()[j].getKolor())
					{
					case 3:
						plik_z_wynikami << tablicaGraczy[i]->zwrocReka()[j].getFigura() << " Kier" << "\t";
						break;
					case 4:
						plik_z_wynikami << tablicaGraczy[i]->zwrocReka()[j].getFigura() << " Karo" << "\t";
						break;
					case 5:
						plik_z_wynikami << tablicaGraczy[i]->zwrocReka()[j].getFigura() << " Trefl" << "\t";
						break;
					case 6:
						plik_z_wynikami << tablicaGraczy[i]->zwrocReka()[j].getFigura() << " Pik" << "\t";
						break;
					}
				}
			}
			plik_z_wynikami.close();
			wcout << "Plik zapisany" << endl;

			break;
		case 2:
			wcout << "Plik nie zostal zapisany" << endl;
			break;

		}

	} while (x < 1 || x > 2);
	system("Pause");
	system("cls");
}




//void Kasyno::dodajGracza(Gracz& _gracz)
//{	
//	if (iloscGraczy == 0) {
//		iloscGraczy++;
//		tablicaGraczy = new Gracz*[iloscGraczy];
//		tablicaGraczy[0] = &_gracz;
//	}
//	else {
//		Gracz **tempGracz;
//		tempGracz = new Gracz*[iloscGraczy];
//		for (int x = 0; x < iloscGraczy; x++) {
//			tempGracz[x] = tablicaGraczy[x];
//		}
//		delete[] tablicaGraczy;
//		iloscGraczy++;
//		tablicaGraczy = new Gracz[iloscGraczy];
//		for (int x = 0; x < iloscGraczy-1; x++) {
//			tablicaGraczy[x] = tempGracz[x];
//		}
//		tablicaGraczy[iloscGraczy - 1] = _gracz;
//	}
//		
//}


