#pragma once
class Ovladac
{
	int teplotaZap;
	int teplotaVyp;

	bool stavCerpadala;

public:
	Ovladac(int tZap, int tVyp);
	void aktualzuj(int tZap, int tVyp);
	void ovladaj(int teplotaA);
	int citajCerpaldo();
};

