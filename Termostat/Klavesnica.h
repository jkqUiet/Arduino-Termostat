#pragma once
class Klavesnica
{
	int vysledok[2];
	int analog;
	bool selecting;

	void sipkaHore(int analog);
	void sipkaDolu(int analog);

	void tlacidkoSelect(int analog);

public:
	Klavesnica();
	int* vyhodnot(int analog);
	void vynuluj();
	bool getSelecting();

};

