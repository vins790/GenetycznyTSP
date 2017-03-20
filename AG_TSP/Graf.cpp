#include "stdafx.h"
#include "Graf.h"


Graf::Graf(string nazwa, bool asymertic) {
	ifstream plik;
	string temp;
	plik.open(nazwa.c_str());

	if (plik.is_open()) {

		do {
			plik >> temp;
		} while (strcmp(temp.c_str(), "DIMENSION:") && strcmp(temp.c_str(), "DIMENSION"));
		plik >> temp;
		if (!strcmp(temp.c_str(), ":"))
			plik >> this->N;
		else {
			this->N = stoi(temp);
		}

		do {
			plik >> temp;
		} while (strcmp(temp.c_str(), "EDGE_WEIGHT_SECTION") && strcmp(temp.c_str(), "EDGE_WEIGHT_SECTION"));

		this->Lista = new float*[N];
		for (int i = 0; i < N; i++) {
			Lista[i] = new float[N];
		}
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				plik >> Lista[i][j];

				if (i == j) Lista[i][j] = -1.0f;
				if (Lista[i][j] == 0) Lista[i][j] = -1.0f;
			}
		}
	}
	else {
		cout << "Blad wczytywania pliku.";
	}
}

Graf::Graf()
{
}

Graf::Graf(string nazwa) {

	ifstream plik;
	string temp;
	plik.open(nazwa.c_str());

	if (plik.is_open()) {

		do {
			plik >> temp;
		} while (strcmp(temp.c_str(), "COMMENT:") && strcmp(temp.c_str(), "COMMENT"));
		plik >> temp;
		if (!strcmp(temp.c_str(), ":"))
			plik >> this->N;
		else
			this->N = stoi(temp);
	}

	float **l = new float*[this->N];
	for (int i = 0; i < N; i++) {
		l[i] = new float[2];
	}

	do {
		plik >> temp;
	} while (strcmp(temp.c_str(), "NODE_COORD_SECTION"));

	int i;
	do {
		plik >> i;

		plik >> temp;
		l[i - 1][0] = stof(temp);
		plik >> temp;
		l[i - 1][1] = stof(temp);
	} while (i<this->N);

	this->Lista = new float*[this->N];
	for (int i = 0; i < this->N; i++) {
		Lista[i] = new float[this->N];
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) {
				Lista[i][j] = -1.0f;
			}
			else {
				Lista[i][j] = sqrt(pow(l[j][0] - l[i][0], 2) + pow(l[j][1] - l[i][1], 2));
			}
		}
	}
}

Graf::~Graf() {
	for (int i = 0; i < N; i++) {
		delete[] Lista[i];
	}
	delete[] Lista;
}

float Graf::koszt(int i, int j) {
	return Lista[i][j];
}

void Graf::pokaz_liste() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << "[" << i << "] [" << j << "] = " << Lista[i][j] << endl;
	}
}

float Graf::oblicz_koszt_permutacji(Osobnik *permutacja) {
	float koszt_calkowity = 0;
	float temp = 0;
	for (int i = 0; i < N - 1; i++) {
		temp = koszt(permutacja->wierzcho쿮k(i), permutacja->wierzcho쿮k(i + 1));
		if (temp == -1) {
			//			if (permutacja->wierzcho쿮k(i) == permutacja->wierzcho쿮k(i + 1))
			return INT_MAX;
		}

		if (temp == 0) {
			return INT_MAX;
		}

		if (temp < 0) {
			return INT_MAX;
		}
		koszt_calkowity += temp;
	}
	koszt_calkowity += koszt(permutacja->wierzcho쿮k(N - 1), permutacja->wierzcho쿮k(0));
	return koszt_calkowity;
}

int Graf::rozmiar() {
	return N;
}