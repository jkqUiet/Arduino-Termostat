#include <Arduino.h>
#include <math.h>
#include <EEPROM.h>

#include "Manazer.h"

#define MAX_POSLEDNE_POUZITE 1000
#define PRVOTNE_NASTAVENIE 50

Manazer::Manazer()
{
	Serial.println("Vytvaram Klavesnicu a Displej a Ovladac !!!!");
	klavesnica = Klavesnica();
	displej = Displej();

	inicializaciaEEPROM();
	testovaciaPomocna = 0;
}

// Funkcia ktora sa vola dokola aby sme to nemuseli mat v LOOpe
void Manazer::pracuj()
{
	displejPraca();
	hodnoty[0][0] = testovaciaPomocna;
	if (testovaciaPomocna < 100) {
		testovaciaPomocna++;
	}
	else {
		testovaciaPomocna = 0;
	}
}

// Pracuje s displejom aktualizuje ho, pohyb v menu atd.
void Manazer::displejPraca()
{
	if (analogRead(0) < 1010) {
		displej.aktualizujVykreslenie(klavesnica.vyhodnot(analogRead(0)), abs(millis()));
		klavesnica.vynuluj();
	}
	if (abs(millis()) % MAX_POSLEDNE_POUZITE > MAX_POSLEDNE_POUZITE - 20 && !displej.getSelecting()) {
		checkAndRefesh();
		displej.aktualizujHodnoty(hodnoty);
	}
}

void Manazer::checkAndRefesh()
{
	if (displej.getZmena()) {
		hodnoty[1][1] = EEPROM.read(5);
		hodnoty[2][1] = EEPROM.read(6);
		hodnoty[3][1] = EEPROM.read(7);
		displej.setZmena();
	}
}

// Vycita z EEPROM pamete a nastavi na prislusne hodnoty v poliach
void Manazer::inicializaciaEEPROM()
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 2; j++) {
			hodnoty[i][j] = PRVOTNE_NASTAVENIE;
		}
	}
	hodnoty[1][1] = EEPROM.read(5);
	hodnoty[2][1] = EEPROM.read(6);
	hodnoty[3][1] = EEPROM.read(7);
}