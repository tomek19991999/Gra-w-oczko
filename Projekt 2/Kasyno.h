#pragma once
#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"

class Kasyno
{
private:
	Karta talia[52];
	Gracz **tablicaGraczy;
		//Bot** tablicaBotow;
	Gracz* wygrany;
	int iloscGraczy;
	int iloscBotow;
	int iloscOddanychKart;
public:
	Kasyno();
	~Kasyno();
	void tasowanie();
	void pokazKarte(int _ktora);
	void pokazWszystkieKarty();
	void graj();
	Karta* dajKarte();
	void dodajGracza();
	void dodajBota(int trybBotow);
	void znalezenieZwyciezcy();
	void usun_graczy();
	void reset();
	void zapisz_wyniki();
	void tworzenieGraczy();
};
