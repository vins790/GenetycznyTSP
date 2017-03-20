#include "stdafx.h"
#include "Test.h"



void Test::TestStart()
{
	Wynik wynik;
	fstream plik;
	plik.open("Wyniki.txt", ios::out);

	if (plik.is_open()) {

		long int Koszt = 0;
		double Czas = 0;


		plik << endl << endl << "TSP ___________________" << endl;
		cout << endl << "Algorytm Genetyczny" << endl << endl;
		cout << "bays29.tsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, true,"sym/bays29.tsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas <<" ms"<< endl<<endl;
		plik << "bays29.tsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		cout << "berlin52.tsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, false, "sym/berlin52.tsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "berlin52.tsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		cout << "ch130.tsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, false, "sym/ch130.tsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "ch130.tsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		cout << "pr299.tsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, false, "sym/pr299.tsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "pr299.tsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;



		plik << endl << endl << "ATSP ___________________" << endl;

		cout << "ftv33.atsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, true, "asym/ftv33.atsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "ftv33.atsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		cout << "ft53.atsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, true, "asym/ft53.atsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "ft53.atsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		cout << "kro124.atsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, true, "asym/kro124p.atsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "kro124p.atsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;


		cout << "ftv170.atsp" << endl;
		for (int i = 0; i < N; i++) {
			wynik = AlgorytmEwolucyjny(500, true, "asym/ftv170.atsp");
			Koszt += wynik.koszt;
			Czas += wynik.czas;
			cout << "czas : " << Czas << " ms" << endl << endl;
		}
		Koszt /= N;
		Czas /= N;
		cout << "czas : " << Czas << " ms" << endl << endl;
		plik << "ftv170.atsp : " << Koszt << " , czas : " << Czas << endl;
		Koszt = 0;
		Czas = 0;

		plik.close();

	}
	else {
		system("CLS");
		cout << "Nie mo¿na utworzyc pliku wynikowego." << endl;
	}
}

Wynik Test::AlgorytmEwolucyjny(int iloscPokolen, bool sposobWczytywania, string sciezka)
{
	Wynik w;

	Graf *g;
	if (sposobWczytywania) {
		g = new Graf(sciezka, true);
	}else {
		g = new Graf(sciezka);
	}
	
	Populacja *p;

	LARGE_INTEGER performanceCountEnd, performanceCountStart;
	LARGE_INTEGER  freq;
	QueryPerformanceFrequency(&freq);

		performanceCountStart = Zegar::startTimer();
		p = new Populacja(900, g);

		for (int i = 0; i < iloscPokolen; i++)
		{
			p->ewolucja(g);
		}
		performanceCountEnd = Zegar::endTimer();
		
		w.koszt = p->zwrocSzczytoweOsiagniecieEwolucji();
		w.czas = ((performanceCountEnd.QuadPart - performanceCountStart.QuadPart) / (double)freq.QuadPart * 1000);
		
		p->wyswietlSzczytoweOsiagniecieEwolucji();
		p->~Populacja();
		g->~Graf();

	return w;
}
