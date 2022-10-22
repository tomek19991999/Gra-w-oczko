#include "Gracz.h"
#include "Kasyno.h"
#include <iostream>
#include <iomanip>

using namespace std;

Gracz::Gracz() {
	reka = nullptr;
	kasynoWsk = nullptr;
	ileKart = 0;
	sumaPunktow = 0;
	pass = 0;
	//wcout << "\naktywacja konstruktor Gracza";
}
Gracz::Gracz(Kasyno& _kasyno) {
	reka = nullptr;
	kasynoWsk = &_kasyno;
	ileKart = 0;
	sumaPunktow = 0;
	pass = false;
	//wcout << "\naktywacja konstruktor Gracza";
	nadajNazwe();
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
	//wcout << endl << "aktywowano konstruktor KOPIUJACY gracza";
}
Gracz::~Gracz() {
	if (reka != nullptr)  delete[] reka; 
	//wcout << "\ndestruktor gracza aktywowany!!";
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
	wcout << endl << "--------------------------------------";
	wcout << endl << "ilosc kart: " << ileKart << "\t\tilosc punktow: " << sumaPunktow<<endl;

}
bool Gracz::czyPass()
{	
	if (sumaPunktow >= 20) {
		pass = true;
		wcout << "\nMasz wiecej niz 19 punktow! Automatyczny pass!\n";
	}
	else {
		wcout << "\ndobierasz czy pasujesz?";
		wcout << "\nwpisz 1 aby dobrac kolejna karte, lub wpisz 0 aby spasowac: ";
		int x;
		do {
			cin >> x;
			if (x < 0 || x>1) wcout << "\nPodaj poprawna liczbe!: ";
			cin.clear(); //kasowanie flagi b³êdu strumienia
			cin.ignore(numeric_limits < std::streamsize >::max(), '\n');
		} while (x < 0 || x>1);
		if(x==0)pass = true;
	}
	return pass;
}
void Gracz::nadajNazwe()
{

	cin >> std::setw(20) >> nazwa;      //zabezpieczenie przed wpisaniem za dlugiego ciagu znakow
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//wcout << "WPROWADZILES: " << nazwa;
}
char* Gracz::zwroc_nick()
{
	return nazwa;
}
bool Gracz::zwrocPass()
{
	return pass;
}
int Gracz::zwrocPunkty()
{
	return sumaPunktow;
}
int Gracz::zwrocIleKart()
{
	return ileKart;
}
Karta* Gracz::zwrocReka()
{
	return reka;
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

//void Gracz::przypiszKasyno(Kasyno& _kasyno) {
//	
//	_kasyno.dodajGracza(*this);
//	kasynoWsk = &_kasyno;
//}
