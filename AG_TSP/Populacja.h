#pragma once
#include "Osobnik.h"
#include "ProfilOsobnika.h"
#include "Graf.h"

class Populacja
{
	ProfilOsobnika* populacja;
	int liczebnosc;
	int sumaDopasowan;
	int N;
	int szczytoweOsiagniecieEwolucji;

public:
	Populacja(int liczebnosc, Graf *g);
	~Populacja();
	void obliczKoszty(Graf *g);
	void obliczDopasowania();
	void zakoduj();
	void odkoduj();
	void ObliczSumeDopasowan();
	void ewolucja(Graf *g);
	int losujRodzica();
	void wyznaczPotomstwo(Osobnik* r1, Osobnik *r2, Osobnik *potomek);
	void wyswietlSzczytoweOsiagniecieEwolucji();
	int zwrocSzczytoweOsiagniecieEwolucji();
};

