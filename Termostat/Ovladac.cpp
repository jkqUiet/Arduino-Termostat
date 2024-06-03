#include "Ovladac.h"

#define KRITICKA_HODNOTA_SPODNA 30
#define KRITICKA_HODNOTA_HORNA 60

Ovladac::Ovladac(int tZap, int tVyp)
{
	teplotaVyp = tVyp;
	teplotaZap = tZap;

	//Stav cerpadla false = vypnuty, true = zapnuty
	stavCerpadala = false;
}

void Ovladac::aktualzuj(int tZap, int tVyp)
{
	teplotaVyp = tVyp;
	teplotaZap = tZap;
}

void Ovladac::ovladaj(int teplotaA)
{
	// na Zapnutie cerpadla
	if (teplotaA >= teplotaZap || teplotaA >= KRITICKA_HODNOTA_HORNA) {
		//	Cerpadlo zopni;
		stavCerpadala = true;
	}

	// na Vypnutie cerpadla
	if (teplotaA <= teplotaVyp || teplotaA <= KRITICKA_HODNOTA_SPODNA) {
		//	Cerpadlo vypni;
		stavCerpadala = false;
	}

}

int Ovladac::citajCerpaldo()
{
	return /*Vratit hodnotu z cerpadla*/;
}
