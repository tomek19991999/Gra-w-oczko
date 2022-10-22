#include "Karta.h"

const char kolory[] = { 3, 4, 5, 6 };
const char figury[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K', 'A' };
const int wartosci[] = { 2,   3,   4,   5,   6,   7 ,  8,   9,  10,   2,   3,   4,  11 };

Karta::Karta(int _kolor, int _wartosc) {
	setKolor(_kolor);
	setWartosc(_wartosc);
}

void Karta::setKolor(int _kolor) {
	if (_kolor < 4) {
		kolor = kolory[_kolor];
	}
}

void Karta::setWartosc(int _wartosc) {
	if (_wartosc < 14) {
		figura = figury[_wartosc];
		wartosc = wartosci[_wartosc];
	}
}

void Karta::wypisz() {
	wcout << endl << "Figura:" << figura << "\t\tKolor:";
	switch (kolor) {
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

wostream& operator<<(wostream& os, const Karta& karta)
{	
	switch (karta.getKolor()) {
	case 3:
		os << "Figura: " << karta.getFigura() << "\tKolor: " << "Kier";
		break;
	case 4:
		os << "Figura: " << karta.getFigura() << "\tKolor: " << "Karo";
		break;
	case 5:
		os << "Figura: " << karta.getFigura() << "\tKolor: " << "Treft";
		break;
	case 6:
		os << "Figura: " << karta.getFigura() << "\tKolor: " << "Pik";
		break;
	}

	return os;
}
