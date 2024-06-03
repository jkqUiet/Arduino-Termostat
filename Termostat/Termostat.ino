/*
 Name:		Termostat.ino
 Created:	2/17/2021 12:07:32 PM
 Author:	qUiet
*/

// the setup function runs once when you press reset or power the board

#include "Manazer.h"

int i;
Manazer man;

void setup() {
	Serial.println("Vytvaram mangera !!");
	man = Manazer();
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Serial.println(analogRead(0));
	//delay(500);

	/*
	select = 720
	lavo = 478
	hore = 131
	dole = 305
	vpravo = 0
	
	*/
	man.pracuj();

}
