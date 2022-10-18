#pragma once
#include "Karta.h"

class Kasyno; //foward declaration
class Gracz
{
private:
	Karta* reka;
	int ileKart;
	int sumaPunktow;
	Kasyno* kasynoWsk;
	bool pass;
public:
	Gracz();
	Gracz(const Gracz& _gracz); //konstruktor kopiujacy, kopiowanie glebokie
	~Gracz();
	void wezKarte(Karta* _karta);
	void pokazReke();
	void przypiszKasyno(Kasyno &_kasyno);

	Gracz& operator =(const Gracz& _gracz); //przypisanie glebokie
};

