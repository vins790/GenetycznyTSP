#include "stdafx.h"
#include "Osobnik.h"



Osobnik::Osobnik()
{
}

Osobnik::Osobnik(int N)
{
	this->N = N;
	for (int i = 0; i < N; i++) {
		DNA.push_back(i);
	}
	std::random_shuffle(&DNA[0], &DNA[this->N]);

}

Osobnik::~Osobnik()
{
	DNA.clear();
	postacKanoniczna.clear();
}

void Osobnik::init()
{
	for (int i = 0; i < N; i++){
		DNA.push_back(i);
	}
	std::random_shuffle(&DNA[0], &DNA[this->N]);

}

void Osobnik::initKanon()
{
	postacKanoniczna.clear();
	for (int i = 0; i < N; i++) {
		postacKanoniczna.push_back(i);
	}
}

int Osobnik::wierzcho³ek(int i)
{
	if (i >= 0 && i < this->N) {
		int w = DNA[i];
		return w;
	}else{
	
		cout << endl<<"B³¹d metody wierzcho³ek"<<endl<< "Niepoprawny indeks!" << endl << "i = " << i << endl << "N = " << this->N << endl << endl;
		system("PAUSE");
		system("EXIT");
	}
}

void Osobnik::wyswietl()
{
	cout << endl << endl << "DNA : ";
	for (int i = 0; i < this->N - 1; i++) {
		cout << this->DNA[i] << " -> ";
	}
	cout << this->DNA[N - 1];
}

void Osobnik::przepisz(Osobnik p)
{
	for (int i = 0; i < this->N; i++) {
		this->DNA[i] = p.wierzcho³ek(i);
	}
}

void Osobnik::zamienWierzcholki(int a, int b)
{
	if (a >= 0 && a < N && b >= 0 && b < N) {
		int temp = DNA[a];
		DNA[a] = DNA[b];
		DNA[b] = temp;
	}
	else {
		cout << endl << "B³¹d metody zamienWierzcho³ek" << endl << "Niepoprawny indeks!" << endl << "a = " << a << endl << "b = " << b << endl << endl;
		system("PAUSE");
		system("EXIT");
	}
}

void Osobnik::mutuj()
{
	int a, b, temp;

	do {
		a = rand() % (N);
		b = rand() % (N);
	} while (a == b);

	swap(DNA[a], DNA[b]);
}

void Osobnik::koduj()
{
	initKanon();
	int j = 0;
	for (int i = 0; i < this->N; i++) {
		
		while (this->DNA[i] != postacKanoniczna[j]) {
			j++;
		}

		for (int n = j; n < this->N - 1; n++){
			postacKanoniczna[n] = postacKanoniczna[n + 1];
		}

		postacKanoniczna[N - 1] = NULL;
		this->DNA[i] = j;
		j = 0;
	
	}
}

void Osobnik::dekoduj()
{
	initKanon();
	int j;
	for (int i = 0; i < this->N; i++)
	{
		j = this->DNA[i];
		this->DNA[i] = postacKanoniczna[this->DNA[i]];
		for (int n = j; n < this->N - 1; n++)
		{
			postacKanoniczna[n] = postacKanoniczna[n + 1];
		}
		postacKanoniczna[N - 1] = NULL;
	}
}

void Osobnik::ustawWierzcholek(int i, int wartosc)
{
	if (i >= 0 && i < N) {
		this->DNA[i] = wartosc;
	}
	else {
		cout << endl << "B³¹d metody ustawWierzcho³ek" << endl << "Niepoprawny indeks!" << endl << "i = " << i << endl << endl;
		system("PAUSE");
		system("EXIT");
	}
}
