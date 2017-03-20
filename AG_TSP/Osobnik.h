#pragma once
#include <vector>
class Osobnik
{
private:
	vector<int> DNA;  // sekwencja reprezentujaca droge
	vector<int> postacKanoniczna;
	int N;


public:
	Osobnik();
	Osobnik(int N);
	~Osobnik();
	void init();
	void initKanon();
	int wierzcho³ek(int i);
	void wyswietl();
	void przepisz(Osobnik p);
	void zamienWierzcholki(int a, int b);
	void mutuj();
	void koduj();
	void dekoduj();
	void ustawWierzcholek(int i, int wartosc);
};

