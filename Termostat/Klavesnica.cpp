#include "Klavesnica.h"
#include <Arduino.h>



/*
    Tlacidla Moje
    select = 720
    lavo = 478
    hore = 131
    dole = 305
    vpravo = 0
*/


Klavesnica::Klavesnica()
{
    selecting = false;
}

int* Klavesnica::vyhodnot(int analog)
{
    
    sipkaDolu(analog);
    sipkaHore(analog);
    tlacidkoSelect(analog);
    return vysledok;
}

void Klavesnica::tlacidkoSelect(int analog)
{
    //select = 720
    if (analog < 750 && analog > 700) {
        selecting = !selecting;
        Serial.println("Selectujem " + analog);
        vysledok[0] = -2;
        vysledok[1] = -2;
    }
   // Serial.println("SELECTUJEM!!");
    
}

void Klavesnica::vynuluj()
{
    vysledok[0] = 0;
    vysledok[1] = 0;
}

bool Klavesnica::getSelecting()
{
    return selecting;
}

void Klavesnica::sipkaHore(int analog)
{
    // hore = 131
    if (analog < 150 && analog > 90) {
        vysledok[0] = 0;
        vysledok[1] = 1;
    }
}

void Klavesnica::sipkaDolu(int analog)
{
    // dole = 305
    if (analog < 325 && analog > 285) {
        vysledok[0] = 0;
        vysledok[1] = -1;
    }
}
