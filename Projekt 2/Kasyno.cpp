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
	wcout << "\naktywacja konstruktor kasyna!";
}
Kasyno::~Kasyno() {
	//if (iloscGraczy > 0) delete[] tablicaGraczy;
	wcout <<endl<< "destruktor kasyna aktywowany!";
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
	Gracz g1;
	Gracz g2;
	dodajGracza(g1);
	dodajGracza(g2);
	//tablicaGraczy[0].wezKarte(dajKarte());
	//tablicaGraczy[0].wezKarte(dajKarte());
	//tablicaGraczy[1].wezKarte(dajKarte());
	//tablicaGraczy[1].wezKarte(dajKarte());
	//tablicaGraczy[0].pokazReke();
	//wcout << "\n\n";
	//tablicaGraczy[1].pokazReke();
}

Karta* Kasyno::dajKarte() {
	iloscOddanychKart++;
		if (iloscOddanychKart < 52) {
			return &talia[iloscOddanychKart - 1];
		}
		else wcout << "Brak kart, koniec gry!";
}

void Kasyno::dodajGracza(Gracz& _gracz)
{	
	if (iloscGraczy == 0) {
		iloscGraczy++;
		tablicaGraczy = new Gracz*[iloscGraczy];
		tablicaGraczy[0] = &_gracz;
	}
	else {
		Gracz *tempGracz;
		tempGracz = new Gracz[iloscGraczy];
		for (int x = 0; x < iloscGraczy; x++) {
			tempGracz[x] = tablicaGraczy[x];
		}
		delete[] tablicaGraczy;
		iloscGraczy++;
		tablicaGraczy = new Gracz[iloscGraczy];
		for (int x = 0; x < iloscGraczy-1; x++) {
			tablicaGraczy[x] = tempGracz[x];
		}
		tablicaGraczy[iloscGraczy - 1] = _gracz;
	}
		
}


