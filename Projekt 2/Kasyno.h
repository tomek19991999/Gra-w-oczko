#pragma once
#include "Karta.h"
#include "Gracz.h"

class Kasyno
{
private:
	Karta talia[52];
	Gracz **tablicaGraczy;
	int iloscGraczy;
	int iloscOddanychKart;
public:
	Kasyno();
	~Kasyno();
	void tasowanie();
	void pokazKarte(int _ktora);
	void pokazWszystkieKarty();
	void graj();
	Karta* dajKarte();
	void dodajGracza(Gracz &_gracz);


};
