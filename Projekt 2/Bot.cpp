#include "Bot.h"

Bot::Bot(Kasyno& _kasyno, int numer, int trybBotow)
	:Gracz()
	{
	kasynoWsk = &_kasyno;
	//wcout << "\naktywacja konstruktor Gracza";
	nazwa[0] = 'B';
	nazwa[1] = 'o';
	nazwa[2] = 't';
	switch (numer) {
		case(1):
			nazwa[3] = '1';
			break;
		case(2):
			nazwa[3] = '2';
			break;
		case(3):
			nazwa[3] = '3';
			break;
	}
	typBota = trybBotow;
}

void Bot::czyPass()
{	
		// typBota - ryzykuj¹cy(1), normalny(2) lub zachowawczy(3)
	if (typBota == 1) {
		if (sumaPunktow>18) {
			pass = true;
		}
	}
	if (typBota == 2) {
		if (sumaPunktow > 17) {
			pass = true;
		}
	}
	if (typBota == 3) {
		if (sumaPunktow > 16) {
			pass = true;
		}
	}
}
