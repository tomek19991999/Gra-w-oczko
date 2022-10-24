#pragma once
#include "Karta.h"

class Kasyno; //foward declaration
class Gracz
{
protected:
	Karta* reka;
	int ileKart;
	int sumaPunktow;
	Kasyno* kasynoWsk;
	bool pass;
	char nazwa[20];
public:
	Gracz();
	Gracz(Kasyno& _kasyno);
	Gracz(const Gracz& _gracz); //konstruktor kopiujacy, kopiowanie glebokie
	~Gracz();
	void wezKarte(Karta* _karta);
	void pokazReke();
	virtual void czyPass(); //zwraca 1 lub 0, w zaleznosci czy pass
	void nadajNazwe(); //funcja nadajaca nazwe graczowi
	char *zwroc_nick();
	bool zwrocPass();
	int zwrocPunkty();
	int zwrocIleKart();
	Karta *zwrocReka();
	//void przypiszKasyno(Kasyno &_kasyno);

	Gracz& operator =(const Gracz& _gracz); //przypisanie glebokie
};

