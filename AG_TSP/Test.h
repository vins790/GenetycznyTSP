#pragma once
#include "Wynik.h"
#include "Graf.h"
#include "Populacja.h"
#include "Zegar.h"

static class Test
{
private:
	static const int N = 1;
public:
	static void TestStart();
	static Wynik AlgorytmEwolucyjny(int iloscPokolen, bool sposobWczytywania, string sciezka);
};


