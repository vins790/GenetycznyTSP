#pragma once
#include "Osobnik.h"

class Graf {

private: float **Lista;
		 int N;

public:
	Graf();
	Graf(string nazwa);
	Graf(string nazwa, bool asymetric);
	~Graf();
	float koszt(int i, int j);
	void pokaz_liste();
	float oblicz_koszt_permutacji(Osobnik *p);
	int rozmiar();

};

