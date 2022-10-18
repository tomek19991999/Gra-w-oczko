#include "Gracz.h"
#include "Kasyno.h"
#include <iostream>

using namespace std;

Gracz::Gracz() {
	reka = nullptr;
	kasynoWsk = NULL;
	ileKart = 0;
	sumaPunktow = 0;
	pass = 0;
	wcout << "\naktywacja konstruktor Gracza";
}
Gracz::Gracz(const Gracz&_gracz) {
	ileKart = _gracz.ileKart;
	sumaPunktow = _gracz.sumaPunktow;

	if (ileKart == 0) {
		reka = nullptr;
	}
	else {
		reka = new Karta[ileKart];
		for (int x = 1; x <= ileKart; x++) {
			reka[x - 1] = _gracz.reka[x - 1];
		}
	}
	wcout << endl << "aktywowano konstruktor KOPIUJACY gracza";
}
Gracz::~Gracz() {
	if (reka != nullptr) { delete[] reka; }
	wcout << "\ndestruktor gracza aktywowany!!";
}
void Gracz::wezKarte(Karta *_karta) {
	if (this == nullptr) wcout << "Najpierw musisz dodac tego gracza!";
	else {
		if (ileKart == 0) {
			ileKart++;
			sumaPunktow += _karta->getWartosc();
			reka = new Karta[ileKart];
			reka[ileKart - 1] = *_karta;
		}
		else {
			Gracz tempGracz;
			tempGracz.ileKart = ileKart;
			tempGracz.sumaPunktow = sumaPunktow;
			tempGracz.reka = new Karta[ileKart];
			for (int x = 1; x <= ileKart; x++) {
				tempGracz.reka[x - 1] = reka[x - 1];
			}
			delete[] reka;
			ileKart++;
			reka = new Karta[ileKart];
			for (int x = 1; x <= tempGracz.ileKart; x++) {
				reka[x - 1] = tempGracz.reka[x - 1];
			}
			reka[ileKart - 1] = *_karta;
			sumaPunktow += _karta->getWartosc();
		}
	}
}
void Gracz::pokazReke() {
	for (int x = 0; x < ileKart; x++) {
		reka[x].wypisz();
	}
	wcout << endl << "ilosc kart: " << ileKart << "   ilosc punktow: " << sumaPunktow;
}
Gracz& Gracz::operator=(const Gracz& _gracz)
{
	//ileKart = _gracz.ileKart;
	//sumaPunktow = _gracz.sumaPunktow;
	if (ileKart == 0) {
		ileKart = _gracz.ileKart;
		sumaPunktow = _gracz.sumaPunktow;
		if (_gracz.ileKart == 0) {
			reka = nullptr;
		}
		else {
			reka = new Karta[ileKart];
			for (int x = 1; x <= ileKart; x++) {
				reka[x - 1] = _gracz.reka[x - 1];
			}
		}

	}
	else {
		ileKart = _gracz.ileKart;
		sumaPunktow = _gracz.sumaPunktow;
		delete[] reka;
		reka = new Karta[ileKart];
		for (int x = 1; x <= ileKart; x++) {
			reka[x - 1] = _gracz.reka[x - 1];
		}
	}
	return *this;
}
void Gracz::przypiszKasyno(Kasyno& _kasyno) {
	
	_kasyno.dodajGracza(*this);
	kasynoWsk = &_kasyno;
}
