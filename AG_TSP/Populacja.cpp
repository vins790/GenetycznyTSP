#include "stdafx.h"
#include "Populacja.h"
#include <vector>

struct indeksDopasowanie {
	int indeks;
	int dopasowanie;
};


Populacja::Populacja(int liczebnosc, Graf *g)
{
	szczytoweOsiagniecieEwolucji = INT_MAX;
	N = g->rozmiar();
	this->liczebnosc = liczebnosc;
	populacja = new ProfilOsobnika[liczebnosc];
	

	int najwiekszyKoszt = -1;

	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].osobnik = new Osobnik(N);
		
		populacja[i].koszt = g->oblicz_koszt_permutacji(populacja[i].osobnik);
		if (populacja[i].koszt > najwiekszyKoszt)
			najwiekszyKoszt = populacja[i].koszt;
	}

	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].dopasowanie = najwiekszyKoszt - populacja[i].koszt;
	}
}

Populacja::~Populacja()
{
	delete populacja;
}

void Populacja::obliczKoszty(Graf *g)
{
	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].koszt = g->oblicz_koszt_permutacji(populacja[i].osobnik);
	}
}

void Populacja::obliczDopasowania()
{
	int najwiekszyKoszt=-1;
	for (int i = 0; i < liczebnosc; i++)
	{
		if (populacja[i].koszt > najwiekszyKoszt)
			najwiekszyKoszt = populacja[i].koszt;
	}

	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].dopasowanie = najwiekszyKoszt - populacja[i].koszt;
	}
}

void Populacja::zakoduj()
{
	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].osobnik->koduj();
	}
}

void Populacja::odkoduj()
{
	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].osobnik->dekoduj();
	}
}

void Populacja::ObliczSumeDopasowan()
{
	sumaDopasowan = 0;
	for (int i = 0; i < liczebnosc; i++)
	{
		sumaDopasowan += populacja[i].dopasowanie;
	}
}

void Populacja::ewolucja(Graf *g)
{
	ObliczSumeDopasowan();
	zakoduj();

	Osobnik **potomstwo = new Osobnik*[liczebnosc];
	indeksDopasowanie * elita = new indeksDopasowanie[liczebnosc];
	for (int i = 0; i < liczebnosc; i++)
	{
		potomstwo[i] = new Osobnik(N);
		elita[i].indeks = i;
		elita[i].dopasowanie = populacja[i].dopasowanie;
	}


	/*for (int i = 0; i < liczebnosc; i++)
	{
		cout << elita[i].dopasowanie << "  indeks: " << elita[i].indeks << endl;
	}*/

	indeksDopasowanie temp;
	for (int i = 0; i < liczebnosc; i++)
	{
		for (int j = 0; j < liczebnosc - 1; j++)
		{
			if (elita[j].dopasowanie < elita[j + 1].dopasowanie) {
				temp.indeks = elita[j].indeks;
				temp.dopasowanie = elita[j].dopasowanie;

				elita[j].indeks = elita[j + 1].indeks;
				elita[j].dopasowanie = elita[j + 1].dopasowanie;
				elita[j + 1].indeks = temp.indeks;
				elita[j + 1].dopasowanie = temp.dopasowanie;
			}
		}
	}


	/*for (int i = 0; i < liczebnosc; i++)
	{
		cout << elita[i].dopasowanie << "  indeks: " << elita[i].indeks<<endl;
	}*/

 	for (int i = 0; i < floor(liczebnosc*0.15); i++)
	{
		potomstwo[i]->przepisz(*populacja[elita[i].indeks].osobnik);
	}
	delete [] elita;
	

	for (int i = floor(liczebnosc*0.15); i < liczebnosc; i++)
	{
		wyznaczPotomstwo(populacja[losujRodzica()].osobnik, populacja[losujRodzica()].osobnik, potomstwo[i]);
	}

	for (int i = 0; i < liczebnosc; i++)
	{
		populacja[i].osobnik->przepisz(*potomstwo[i]);
	}

	for (int z = 0; z < liczebnosc; z++)
	{
		if (potomstwo[z] != nullptr)
		delete potomstwo[z];
	}
	delete[]  potomstwo;
		
	odkoduj();
	for (int i = 0; i < liczebnosc; i++)
	{
		if (rand() % 1000 < 7) {
			populacja[i].osobnik->mutuj();
		}
	}
	obliczKoszty(g);
	obliczDopasowania();

	int kosztMinimalny = INT_MAX;
	for (int i = 0; i < liczebnosc; i++)
	{
		if (populacja[i].koszt < kosztMinimalny) kosztMinimalny = populacja[i].koszt;
	}

	//cout << endl << "Obecnie najlepszy : " << kosztMinimalny;

	if (kosztMinimalny < szczytoweOsiagniecieEwolucji)
		szczytoweOsiagniecieEwolucji = kosztMinimalny;

}

int Populacja::losujRodzica()
{
	int los = rand() % (sumaDopasowan);
	int suma = 0;
	
	for (int i = 0; i < liczebnosc; i++)
	{
		if (suma <= los) {
			suma += populacja[i].dopasowanie;
		}
		else {
			return i;
		}
	}
	return liczebnosc-1;
	cout << endl << "B낱d funkcji losujRodzica!" << endl<<endl;
	system("PAUSE");
	system("EXIT");
}

void Populacja::wyznaczPotomstwo(Osobnik* r1, Osobnik *r2, Osobnik *potomek)
{
	int	k[10];

	int i = 0;
	bool randomizeCondition = false;
	for (int z = 0; z < 10; z++) {
		do {
			randomizeCondition = false;
			k[i] = rand() % N;

			for (int j = 0; j < i; j++)
			{
				if (k[j] == k[i]) {
					randomizeCondition = true;
				}
			}

		} while (randomizeCondition);
		i++;
	}

	sort(k, k+10);

	//for (int i = 0; i < 9; i++)
	//{
	//	cout << k[i] << " , ";
	//}
	//
	//cout << k[9] << endl << endl;

	//cout << "r1 : " << endl;
	//r1->wyswietl();
	//r1->dekoduj();
	//r1->wyswietl();
	//r1->koduj();

	//cout <<endl<< "r2 : " << endl;
	//r2->wyswietl();
	//r2->dekoduj();
	//r2->wyswietl();
	//r2->koduj();
	
		for (int i = 0; i < k[0]; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		for (int i = k[0]; i < k[1]; i++)
		{
			potomek->ustawWierzcholek(i, r2->wierzcho쿮k(i));
		}
		for (int i = k[1]; i < k[2]; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		for (int i = k[2]; i < k[3]; i++)
		{
			potomek->ustawWierzcholek(i, r2->wierzcho쿮k(i));
		}
		for (int i = k[3]; i < k[4]; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		for (int i = k[4]; i < k[5]; i++)
		{
			potomek->ustawWierzcholek(i, r2->wierzcho쿮k(i));
		}
		for (int i = k[5]; i < k[6]; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		for (int i = k[6]; i < k[7]; i++)
		{
			potomek->ustawWierzcholek(i, r2->wierzcho쿮k(i));
		}
		for (int i = k[7]; i < k[8]; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		for (int i = k[8]; i < k[9]; i++)
		{
			potomek->ustawWierzcholek(i, r2->wierzcho쿮k(i));
		}
		for (int i = k[9]; i < N; i++)
		{
			potomek->ustawWierzcholek(i, r1->wierzcho쿮k(i));
		}
		
		/*cout << endl << endl << "potomek : " << endl;
		potomek->wyswietl();
		potomek->dekoduj();
		potomek->wyswietl();*/
}

void Populacja::wyswietlSzczytoweOsiagniecieEwolucji()
{
	cout << "**********" << endl;
	cout << "* " << szczytoweOsiagniecieEwolucji << endl;
	cout << "**********" << endl;
}

int Populacja::zwrocSzczytoweOsiagniecieEwolucji()
{
	return szczytoweOsiagniecieEwolucji;
}
