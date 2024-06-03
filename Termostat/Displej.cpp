#include <math.h>
#include <EEPROM.h>
#include <Arduino.h>

#include "Displej.h"

#define POCET_PODMENU 6
#define DELAY_DISPLEJA 200
#define ZACIATOCNE_MENU 4
#define SELECT_VALUE -2
#define CHYBA_SENZORU -127
#define DELAY_NASTAVENIA 30


Displej::Displej()
{
	aktObr = ZACIATOCNE_MENU;
	disPoslednePouzitie = 0;
	lcd = new LiquidCrystal(8, 9, 4, 5, 6, 7);
	selecting = false;
	zmenenaEEPROM = false;

	definovanieNeziaducichObr();
	setAllowedObr();
	inicializujMenu();
	iniDisplej();
	vykresli();
}

// Vykresluje displej
void Displej::vykresli()
{
	lcd->clear();
	lcd->setCursor(0, 0);
	
		if (!neziaduceObrazovky()) {
			for (int i = 0; i < 2; i++) {
			lcd->print(menuNazvy[aktObr][i]);
			if (menuHodnoty[aktObr][i] != CHYBA_SENZORU) {
				lcd->print(menuHodnoty[aktObr][i]);
			}
			else {
				lcd->print("Chyba");
			}
			lcd->setCursor(0, 1);
			}
		}
		else {
			lcd->print(menuNazvy[aktObr][0]);
			lcd->setCursor(0, 1);
			if (menuHodnoty[aktObr][1] != CHYBA_SENZORU) {
				lcd->print(menuHodnoty[aktObr][1]);
			}
			else {
				lcd->print("Chyba");
			}
		}
	if (selecting) {
		lcd->setCursor(15,1);
		lcd->print("S");
	}	
	
}

void Displej::aktualizujVykreslenie(int pozPozicia[2], int cas)
{
	if (casovanieDispleja(cas)) {
		if (!selecting) {
			if (trySelect(pozPozicia)) {
				selecting = true;
			}
			else {
				aktObr += pozPozicia[1];
				if (aktObr >= POCET_PODMENU) {
					aktObr = 0;
				}
				if (aktObr < 0) {
					aktObr = POCET_PODMENU - 1;
				}
			}		
		}
		else {
			if (trySelect(pozPozicia)) {
				zapisEEPROM();
				selecting = false;
			} else {
				if (checkHranice()) {
					menuHodnoty[aktObr][1] += pozPozicia[1];
				}
				else {
					menuHodnoty[aktObr][1] += checkKtoraHranica();
				}
			}
		}		
		setPodsvietenie();
		vykresli();

		disPoslednePouzitie = cas;
	}
}

/* Aktualizuje hodnoty - teploty atd. je to duplicitne s managerom s dovodu keby 
   toto padlo aby termostat dalej fungoval.*/
void Displej::aktualizujHodnoty(int hodnoty[6][2])
{
	bool zmena = false;
		for (int j = 0; j < 2; j++) {
			if (menuHodnoty[aktObr][j] != hodnoty[aktObr][j]) {
				menuHodnoty[aktObr][j] = hodnoty[aktObr][j];
				zmena = true;
			}
		}
	if (zmena) {
		vykresli();
	}
}

bool Displej::getSelecting()
{
	return selecting;
}

void Displej::setZmena()
{
	zmenenaEEPROM = false;
}

bool Displej::casovanieDispleja(int cas)
{
	return abs(cas - disPoslednePouzitie) > DELAY_DISPLEJA;
}

bool Displej::trySelect(int pozPozicia[2])
{
	return pozPozicia[0] == SELECT_VALUE && pozPozicia[1] == SELECT_VALUE && getSelectingAllowed();
}

bool Displej::getZmena()
{
	return zmenenaEEPROM;
}

void Displej::setPodsvietenie()
{
	analogWrite(10, menuHodnoty[3][1] * 2.5);
}

// Inicializuje displej
void Displej::iniDisplej()
{
	lcd->begin(16,2);
	lcd->clear();
	lcd->setCursor(1,0);
	lcd->print("Ahoj termostat");
	lcd->setCursor(5,1);
	lcd->print("2021");
}

// Inicializuje menu a hranice
void Displej::inicializujMenu()
{
	aktObr = 0;
	iniMenuNazvy();
	iniMenuHranice();
}

/* Kontroluje ci sa niektore podmenu nenachadza v neziaducich obrazovkach teda na jednom riadku 
   nieco napisame a na druhom cislo*/
bool Displej::neziaduceObrazovky()
{
	for (int i = 0; i < POCET_NEZ_OBR; i++) {
		if (neziaduceObr[i] == aktObr) {
			return true;
		}
	}
	return false;
}

// Tu definujem neziaduce obrazovky
void Displej::definovanieNeziaducichObr()
{
	neziaduceObr[0] = 1;
	neziaduceObr[1] = 2;
	neziaduceObr[2] = 3;
}

void Displej::setAllowedObr()
{
	selectAllowed[0] = 1;
	selectAllowed[1] = 2;
	selectAllowed[2] = 3;
}

bool Displej::checkHranice()
{
	return menuHranice[aktObr][0] > menuHodnoty[aktObr][1] && menuHodnoty[aktObr][1] > menuHranice[aktObr][1];
}

int Displej::checkKtoraHranica()
{
	if (menuHranice[aktObr][0] == menuHodnoty[aktObr][1]) {
		return -1;
	}
	return 1;
}

void Displej::zapisEEPROM()
{
	EEPROM.write(5,menuHodnoty[1][1]);
	EEPROM.write(6,menuHodnoty[2][1]);
	EEPROM.write(7,menuHodnoty[3][1]);
	zmenenaEEPROM = true;
}

bool Displej::getSelectingAllowed()
{
	bool var = false;
	for (int i = 0; i < POCET_OBRAZOVIEK_MOZNYCH_ZMIEN; i++) {
		if (aktObr == selectAllowed[i]) {
			var = true;
			break;
		}
	}
	return var;
}

// Inicializacia samotneho menu - Tu pridavame dalsie polozky
void Displej::iniMenuNazvy()
{
	menuNazvy[0][0] = "Vonku    :";
	menuNazvy[0][1] = "Cerpadlo :";

	menuNazvy[1][0] = "Nast.cerpad.zap :";
	menuNazvy[1][1] = "";

	menuNazvy[2][0] = "Nast.cerpad.vyp :";
	menuNazvy[2][1] = "";

	menuNazvy[3][0] = "Podsvietenie LCD :";
	menuNazvy[3][1] = "";

	menuNazvy[4][0] = "Kotol    :";
	menuNazvy[4][1] = "Bojler   :";

	menuNazvy[5][0] = "Pivnica  :";
	menuNazvy[5][1] = "Vlhkost  :";
}

// Inicializacia hranic
void Displej::iniMenuHranice()
{
	/**Ak je tam -255 tak dane podmenu nema hranicu
	*
	* vzdy je inicializovane najprv Maximum potom minimum !!!!!
	*/	

	menuHranice[0][0] = -255;
	menuHranice[0][1] = -255;

	menuHranice[1][0] = 100;
	menuHranice[1][1] = 0;

	menuHranice[2][0] = 100;
	menuHranice[2][1] = 0;

	menuHranice[3][0] = 100;
	menuHranice[3][1] = 0;

	menuHranice[4][0] = -255;
	menuHranice[4][1] = -255;

	menuHranice[5][0] = -255;
	menuHranice[5][1] = -255;
}
