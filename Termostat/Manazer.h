#pragma once

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#include "Klavesnica.h"
#include "Displej.h"

class Manazer
{
	Displej displej;
	Klavesnica klavesnica;

	int testovaciaPomocna;

	void displejPraca();

	void inicializaciaEEPROM();
	void checkAndRefesh();

	int hodnoty[6][2];

public:
	
	Manazer();
	void pracuj();

};

