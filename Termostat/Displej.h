#pragma once
#include <LiquidCrystal.h>

#define POCET_NEZ_OBR 3
#define POCET_OBRAZOVIEK_MOZNYCH_ZMIEN 3


class Displej
{
	LiquidCrystal *lcd;
	int aktObr;
	int disPoslednePouzitie;
	int neziaduceObr[POCET_NEZ_OBR];
	int selectAllowed[POCET_OBRAZOVIEK_MOZNYCH_ZMIEN];

	bool selecting;
	bool zmenenaEEPROM;

	void iniMenuNazvy();
	void iniMenuHranice();

	void iniDisplej();
	void inicializujMenu();
	bool neziaduceObrazovky();
	void definovanieNeziaducichObr();
	void setAllowedObr();
	bool checkHranice();
	int checkKtoraHranica();
	void setPodsvietenie();
	
	bool casovanieDispleja(int cas);
	bool trySelect(int pozPozicia[2]);

protected:
	String menuNazvy[6][2]; // 1 : polozky v menu, 2 : riadky, 3 : Nazov, 4 : hodnota, 5 : hranica
	int menuHranice[6][2];
	int menuHodnoty[6][2];

public:
	Displej();
	void aktualizujVykreslenie(int pozPozicia[2], int cas);
	void aktualizujHodnoty(int hodnoty[6][2]);

	bool getSelecting();
	bool getZmena();
	
	void zapisEEPROM();
	void setZmena();

	bool getSelectingAllowed();

	void vykresli();
};

