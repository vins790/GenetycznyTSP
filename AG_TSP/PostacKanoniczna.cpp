#include "stdafx.h"
#include "PostacKanoniczna.h"

void PostacKanoniczna::init(int N)
{
	kanon = new int[N];
	for (int i = 0; i < N; i++) {
		kanon[i] = i;
	}
}
