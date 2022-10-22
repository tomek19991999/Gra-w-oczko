#pragma once
#include <iostream>
#include <io.h>
#include <fcntl.h>
using namespace std;

class Karta {
private:
	char kolor;
	char figura;
	int wartosc;
public:
	Karta(int _kolor = 0, int _wartosc = 0); //kolor od 0 do 3, wartosc od 0 do 13 (watosc to cyferka, ew dama itd)
	void setKolor(int _kolor);
	void setWartosc(int _wartosc);
	char getKolor() const { return kolor; }
	char getFigura() const { return figura; }
	int getWartosc() const { return wartosc; }
	void wypisz();
	friend wostream& operator<<(wostream& os, const Karta& dt);
};
