#include "game.h"

int VEL_MAT = 4;

char traziPotez(int** a);

//dinamicka alokacija/oslobadjanje memorije
int** uzmiMemoriju()
{
	int** a;
	a = calloc(VEL_MAT, sizeof(int*));
	if (!a) exit(0);
	for (int i = 0; i < VEL_MAT; i++)
	{
		a[i] = calloc(VEL_MAT, sizeof(int));
		if (!a[i]) exit(0);
	} return a;
}
void vratiMemoriju(int** a)
{
	for (int i = 0; i < VEL_MAT; i++) free(a[i]);
	free(a);
}
//kopiranje i poredjenje sadrzaja matrica
int** deepCopy(int** a)
{
	int** kopija = uzmiMemoriju();
	for (int i = 0; i < VEL_MAT; i++) for (int j = 0; j < VEL_MAT; j++) kopija[i][j] = a[i][j];

	return kopija;
}
int isteMatrice(int** a, int** b)
{
	for (int i = 0; i < VEL_MAT; i++)
	{
		for (int j = 0; j < VEL_MAT; j++)
		{
			if (a[i][j] != b[i][j]) return 0;
		}
	}
	return 1;
}
//generisanje random elementa i provera slobodnih mesta
int imaSlobodnih(int** a)
{
	for (int i = 0; i < VEL_MAT; i++) for (int j = 0; j < VEL_MAT; j++) if (a[i][j] == 0) return 1;
	return 0;
}
int** generisiRandomElement(int** a, int* novii, int* novij)
{
	if (imaSlobodnih(a))
	{
		int i, j;
		do {
			i = rand() % VEL_MAT;
			j = rand() % VEL_MAT;
		} while (a[i][j] != 0);
		//10% sanse da se pojavi 4, inace ide 2
		int vr = rand() % 10;
		if (vr == 0) a[i][j] = 4;
		else a[i][j] = 2;
		*novii = i;
		*novij = j;
	}
	return a;
}
//win sistem
int pobeda(int** a)
{
	for (int i = 0; i < VEL_MAT; i++) for (int j = 0; j < VEL_MAT; j++) if (a[i][j] == 2048) return 1;
	return 0;
}
//provera ima li mogucih poteza
int postojePotezi(int** a)
{
	if (imaSlobodnih(a)) return 1;

	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (d < VEL_MAT && p < VEL_MAT)
		{
			if (a[i][p] == 0) p++;
			else if (a[i][p] != a[i][d] && a[i][d] != 0) p = d;
			else if (a[i][p] != 0 && a[i][p] == a[i][d]) return 1;
			d++;
		}
	}
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (a[p][i] == 0) p--;
			else if (a[p][i] != a[d][i] && a[d][i] != 0) p = d;
			else if (a[p][i] != 0 && a[p][i] == a[d][i]) return 1;
			d--;
		}
	}
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (a[i][p] == 0) p--;
			else if (a[i][p] != a[i][d] && a[i][d] != 0) p = d;
			else if (a[i][p] != 0 && a[i][p] == a[i][d]) return 1;
			d--;
		}
	}
	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (d < VEL_MAT && p < VEL_MAT)
		{
			if (a[p][i] == 0) p++;
			else if (a[p][i] != a[d][i] && a[d][i] != 0) p = d;
			else if (a[p][i] != 0 && a[p][i] == a[d][i]) return 1;
			d++;
		}
	}
	return 0;
}

//Pokretanje odgovarajuce akcije nad matricom igre u odnosu na input, zapis svih poteza u strukturu 
int** pomeranjeElemenata(int** a, Pomeranja* pom, int* brojPomeranja)
{
	if (app.keyboard[SDL_SCANCODE_LEFT])//pomeranje levo
	{
		for (int i = 0; i < VEL_MAT; i++)
		{
			int p = 0, d = 1;
			while (p < VEL_MAT && d < VEL_MAT)
			{
				if (a[i][p] != 0) p++;
				else if (a[i][p] == 0 && a[i][d] != 0)
				{
					a[i][p] = a[i][d];
					a[i][d] = 0;
					pom[*brojPomeranja].spajanje = 0;
					pom[*brojPomeranja].x1 = i;
					pom[*brojPomeranja].x2 = i;
					pom[*brojPomeranja].y1 = d;
					pom[*brojPomeranja].y2 = p;
					*brojPomeranja = *brojPomeranja + 1;
					p++;
				}
				d++;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_DOWN])//pomeranje dole
	{
		for (int i = VEL_MAT - 1; i >= 0; i--)
		{
			int p = VEL_MAT - 1, d = p - 1;
			while (d >= 0 && p >= 0)
			{
				if (a[p][i] != 0) p--;
				else if (a[p][i] == 0 && a[d][i] != 0)
				{
					a[p][i] = a[d][i];
					a[d][i] = 0;
					pom[*brojPomeranja].spajanje = 0;
					pom[*brojPomeranja].x1 = d;
					pom[*brojPomeranja].x2 = p;
					pom[*brojPomeranja].y1 = i;
					pom[*brojPomeranja].y2 = i;
					*brojPomeranja = *brojPomeranja + 1;
					p--;
				}
				d--;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_RIGHT])//pomeranje desno
	{
		for (int i = VEL_MAT - 1; i >= 0; i--)
		{
			int p = VEL_MAT - 1, d = p - 1;
			while (d >= 0 && p >= 0)
			{
				if (a[i][p] != 0) p--;
				else if (a[i][p] == 0 && a[i][d] != 0)
				{
					a[i][p] = a[i][d];
					a[i][d] = 0;
					pom[*brojPomeranja].spajanje = 0;
					pom[*brojPomeranja].x1 = i;
					pom[*brojPomeranja].x2 = i;
					pom[*brojPomeranja].y1 = d;
					pom[*brojPomeranja].y2 = p;
					*brojPomeranja = *brojPomeranja + 1;
					p--;
				}
				d--;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_UP])//pomeranje gore
	{
		for (int i = 0; i < VEL_MAT; i++)
		{
			int p = 0, d = 1;
			while (d < VEL_MAT && p < VEL_MAT)
			{
				if (a[p][i] != 0) p++;
				else if (a[p][i] == 0 && a[d][i] != 0)
				{
					a[p][i] = a[d][i];
					a[d][i] = 0;
					pom[*brojPomeranja].spajanje = 0;
					pom[*brojPomeranja].x1 = d;
					pom[*brojPomeranja].x2 = p;
					pom[*brojPomeranja].y1 = i;
					pom[*brojPomeranja].y2 = i;
					*brojPomeranja = *brojPomeranja + 1;
					p++;
				}
				d++;
			}
		}
	}
	return a;
}
int** unosPoteza(int** a, int** undo, int* score, int* vraceno, int undoscore)//unos poteza i spajanje onoga sto moze da se spoji
{
	stage.brojPomeranja = 0;
	pom = malloc(20*sizeof(Pomeranja));
	int** kopija = deepCopy(a);
	if (app.keyboard[SDL_SCANCODE_B])//vracanje na prethodni potez
	{
		vratiMemoriju(a);
		vratiMemoriju(kopija);
		*vraceno += 1;
		*score = undoscore;
		return undo;
	}

	if (app.keyboard[SDL_SCANCODE_H])//automatski odradjen sledeci potez - hint
	{
		char move = traziPotez(a);
		app.keyboard[SDL_SCANCODE_LEFT] = 0;
		app.keyboard[SDL_SCANCODE_DOWN] = 0;
		app.keyboard[SDL_SCANCODE_RIGHT] = 0;
		app.keyboard[SDL_SCANCODE_UP] = 0;
		if (move == 'a') app.keyboard[SDL_SCANCODE_LEFT] = 1;
		if (move == 's') app.keyboard[SDL_SCANCODE_DOWN] = 1;
		if (move == 'd') app.keyboard[SDL_SCANCODE_RIGHT] = 1;
		if (move == 'w') app.keyboard[SDL_SCANCODE_UP] = 1;
	}

	if (app.keyboard[SDL_SCANCODE_LEFT])//pomeranje levo
	{
		for (int i = 0; i < VEL_MAT; i++)
		{
			int p = 0, d = 1;
			while (d < VEL_MAT && p < VEL_MAT)
			{
				if (a[i][p] == 0) p++;
				else if (a[i][p] != a[i][d] && a[i][d] != 0) p = d;
				else if (a[i][p] != 0 && a[i][p] == a[i][d])
				{
					a[i][p] *= 2;
					a[i][d] = 0;
					pom[stage.brojPomeranja].spajanje = 1;
					pom[stage.brojPomeranja].x1 = i;
					pom[stage.brojPomeranja].x2 = i;
					pom[stage.brojPomeranja].y1 = d;
					pom[stage.brojPomeranja++].y2 = p;
					*score += a[i][p];//povecanje skora
					p++;
				}
				d++;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_DOWN])//pomeranje dole
	{
		for (int i = VEL_MAT - 1; i >= 0; i--)
		{
			int p = VEL_MAT - 1, d = p - 1;
			while (d >= 0 && p >= 0)
			{
				if (a[p][i] == 0) p--;
				else if (a[p][i] != a[d][i] && a[d][i] != 0) p = d;
				else if (a[p][i] != 0 && a[p][i] == a[d][i])
				{
					a[p][i] *= 2;
					a[d][i] = 0;
					pom[stage.brojPomeranja].spajanje = 1;
					pom[stage.brojPomeranja].x1 = d;
					pom[stage.brojPomeranja].x2 = p;
					pom[stage.brojPomeranja].y1 = i;
					pom[stage.brojPomeranja++].y2 = i;
					*score += a[p][i];//povecanje skora
					p--;
				}
				d--;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_RIGHT])//pomeranje desno
	{
		for (int i = VEL_MAT - 1; i >= 0; i--)
		{
			int p = VEL_MAT - 1, d = p - 1;
			while (d >= 0 && p >= 0)
			{
				if (a[i][p] == 0) p--;
				else if (a[i][p] != a[i][d] && a[i][d] != 0) p = d;
				else if (a[i][p] != 0 && a[i][p] == a[i][d])
				{
					a[i][p] *= 2;
					a[i][d] = 0;
					pom[stage.brojPomeranja].spajanje = 1;
					pom[stage.brojPomeranja].x1 = i;
					pom[stage.brojPomeranja].x2 = i;
					pom[stage.brojPomeranja].y1 = d;
					pom[stage.brojPomeranja++].y2 = p;
					*score += a[i][p];//povecanje skora
					p--;
				}
				d--;
			}
		}
	}
	else if (app.keyboard[SDL_SCANCODE_UP])//pomeranje gore
	{
		for (int i = 0; i < VEL_MAT; i++)
		{
			int p = 0, d = 1;
			while (d < VEL_MAT && p < VEL_MAT)
			{
				if (a[p][i] == 0) p++;
				else if (a[p][i] != a[d][i] && a[d][i] != 0) p = d;
				else if (a[p][i] != 0 && a[p][i] == a[d][i])
				{
					a[p][i] *= 2;
					a[d][i] = 0;
					pom[stage.brojPomeranja].spajanje = 1;
					pom[stage.brojPomeranja].x1 = d;
					pom[stage.brojPomeranja].x2 = p;
					pom[stage.brojPomeranja].y1 = i;
					pom[stage.brojPomeranja++].y2 = i;
					*score += a[p][i];//povecanje skora
					p++;
				}
				d++;
			}
		}
	}
	if (app.keyboard[SDL_SCANCODE_R])
	{
		vratiMemoriju(a);
		vratiMemoriju(kopija);
		a = uzmiMemoriju();
		generisiRandomElement(a, &stage.novii, &stage.novij);
		*vraceno = 2;
		*score = 0;
		return a;
	}
	//nakon spajanja onih koji to mogu, pomeram spojene elemente
	a = pomeranjeElemenata(a,pom,&stage.brojPomeranja);
	for (int i = 0; i < stage.brojPomeranja; i++)
	{
		for (int j = i + 1; j < stage.brojPomeranja; j++)
		{
			if (pom[i].spajanje == 1 && pom[j].spajanje == 0 && pom[i].x2 == pom[j].x1 && pom[i].y2 == pom[j].y1)
			{
				pom[i].x2 = pom[j].x2;
				pom[i].y2 = pom[j].y2;
				break;
			}
		}
	}
	//provera da li se desilo nesto
	if (!isteMatrice(a, kopija))
	{
		vratiMemoriju(kopija);
		return a;
	}
	return a;
}


//hint sistem
float evaluacijaPozicije(int** a, int putanja, float baza)
{
	float score = 0;
	int stepen = 0;
	int pravac = 1;
	int i, j;
	switch (putanja)
	{
	case 1:
		i = 0;
		j = 0;
		while (i < VEL_MAT)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[i][j] * pow(baza, stepen++);
				if (pravac == 1) j++;
				else j--;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j--;
			}
			else
			{
				pravac = -pravac;
				j++;
			}
			i++;
		}
		return score;
	case 2:
		i = 0;
		j = 0;
		while (i < VEL_MAT)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[j][i] * pow(baza, stepen++);
				if (pravac == 1) j++;
				else j--;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j--;
			}
			else
			{
				pravac = -pravac;
				j++;
			}
			i++;
		}
		return score;
	case 3:
		i = 3;
		j = 0;
		while (i >= 0)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[i][j] * pow(baza, stepen++);
				if (pravac == 1) j++;
				else j--;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j--;
			}
			else
			{
				pravac = -pravac;
				j++;
			}
			i--;
		}
		return score;
	case 4:
		i = 0;
		j = 3;
		while (i < VEL_MAT)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[j][i] * pow(baza, stepen++);
				if (pravac == 1) j--;
				else j++;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j++;
			}
			else
			{
				pravac = -pravac;
				j--;
			}
			i++;
		}
		return score;
	case 5:
		i = 3;
		j = 0;
		while (i >= 0)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[i][j] * pow(baza, stepen++);
				if (pravac == 1) j++;
				else j--;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j--;
			}
			else
			{
				pravac = -pravac;
				j++;
			}
			i--;
		}
		return score;
	case 6:
		i = 0;
		j = 3;
		while (i < VEL_MAT)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[j][i] * pow(baza, stepen++);
				if (pravac == 1) j--;
				else j++;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j++;
			}
			else
			{
				pravac = -pravac;
				j--;
			}
			i++;
		}
		return score;
	case 7:
		i = 3;
		j = 3;
		while (i >= 0)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[i][j] * pow(baza, stepen++);
				if (pravac == 1) j--;
				else j++;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j++;
			}
			else
			{
				pravac = -pravac;
				j--;
			}
			i--;
		}
		return score;
	case 8:
		i = 3;
		j = 3;
		while (i >= 0)
		{
			while (j >= 0 && j < VEL_MAT)
			{
				score += a[j][i] * pow(baza, stepen++);
				if (pravac == 1) j--;
				else j++;
			}
			if (pravac == 1)
			{
				pravac = -pravac;
				j++;
			}
			else
			{
				pravac = -pravac;
				j--;
			}
			i--;
		}
		return score;
	}
}
char generisiPoteze(int** trenutnoStanje, int dubina, int maxDubina, int baza, float* scoreBest)
{
	float bestScore = -1;
	char bestMove = ' ';
	float score;
	char c;
	int noviScore;
	int** kopija;
	//potez levo
	kopija = deepCopy(trenutnoStanje);
	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (d < VEL_MAT && p < VEL_MAT)
		{
			if (kopija[i][p] == 0) p++;
			else if (kopija[i][p] != kopija[i][d] && kopija[i][d] != 0) p = d;
			else if (kopija[i][p] != 0 && kopija[i][p] == kopija[i][d])
			{
				kopija[i][p] *= 2;
				kopija[i][d] = 0;
				p++;
			}
			d++;
		}
	}
	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (p < VEL_MAT && d < VEL_MAT)
		{
			if (kopija[i][p] != 0) p++;
			else if (kopija[i][p] == 0 && kopija[i][d] != 0)
			{
				kopija[i][p] = kopija[i][d];
				kopija[i][d] = 0;
				p++;
			}
			d++;
		}
	}
	if (!isteMatrice(kopija, trenutnoStanje))
	{
		for (int i = 1; i < 9; i++)
		{
			score = evaluacijaPozicije(kopija, i, 0.5);
			noviScore = 0;
			if (dubina != 0)
			{
				c = generisiPoteze(kopija, dubina - 1, maxDubina, baza, &noviScore);
				score += noviScore * pow(baza, maxDubina - dubina + 1);
			}
			if (score > bestScore)
			{
				bestMove = 'a';
				bestScore = score;
			}
			score -= noviScore;
		}
		vratiMemoriju(kopija);
	}
	else vratiMemoriju(kopija);
	//potez desno
	kopija = deepCopy(trenutnoStanje);
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (kopija[i][p] == 0) p--;
			else if (kopija[i][p] != kopija[i][d] && kopija[i][d] != 0) p = d;
			else if (kopija[i][p] != 0 && kopija[i][p] == kopija[i][d])
			{
				kopija[i][p] *= 2;
				kopija[i][d] = 0;
				p--;
			}
			d--;
		}
	}
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (kopija[i][p] != 0) p--;
			else if (kopija[i][p] == 0 && kopija[i][d] != 0)
			{
				kopija[i][p] = kopija[i][d];
				kopija[i][d] = 0;
				p--;
			}
			d--;
		}
	}
	if (!isteMatrice(kopija, trenutnoStanje))
	{
		for (int i = 1; i < 9; i++)
		{
			score = evaluacijaPozicije(kopija, i, 0.5);
			noviScore = 0;
			if (dubina != 0)
			{
				c = generisiPoteze(kopija, dubina - 1, maxDubina, baza, &noviScore);
				score += noviScore * pow(baza, maxDubina - dubina + 1);
			}
			if (score > bestScore)
			{
				bestMove = 'd';
				bestScore = score;
			}
			score -= noviScore;
		}
		vratiMemoriju(kopija);
	}
	else vratiMemoriju(kopija);
	//potez gore
	kopija = deepCopy(trenutnoStanje);
	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (d < VEL_MAT && p < VEL_MAT)
		{
			if (kopija[p][i] == 0) p++;
			else if (kopija[p][i] != kopija[d][i] && kopija[d][i] != 0) p = d;
			else if (kopija[p][i] != 0 && kopija[p][i] == kopija[d][i])
			{
				kopija[p][i] *= 2;
				kopija[d][i] = 0;
				p++;
			}
			d++;
		}
	}
	for (int i = 0; i < VEL_MAT; i++)
	{
		int p = 0, d = 1;
		while (d < VEL_MAT && p < VEL_MAT)
		{
			if (kopija[p][i] != 0) p++;
			else if (kopija[p][i] == 0 && kopija[d][i] != 0)
			{
				kopija[p][i] = kopija[d][i];
				kopija[d][i] = 0;
				p++;
			}
			d++;
		}
	}
	if (!isteMatrice(kopija, trenutnoStanje))
	{
		for (int i = 1; i < 9; i++)
		{
			score = evaluacijaPozicije(kopija, i, 0.5);
			noviScore = 0;
			if (dubina != 0)
			{
				c = generisiPoteze(kopija, dubina - 1, maxDubina, baza, &noviScore);
				score += noviScore * pow(baza, maxDubina - dubina + 1);
			}
			if (score > bestScore)
			{
				bestMove = 'w';
				bestScore = score;
			}
			score -= noviScore;
		}
		vratiMemoriju(kopija);
	}
	else vratiMemoriju(kopija);
	//potez dole
	kopija = deepCopy(trenutnoStanje);
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (kopija[p][i] == 0) p--;
			else if (kopija[p][i] != kopija[d][i] && kopija[d][i] != 0) p = d;
			else if (kopija[p][i] != 0 && kopija[p][i] == kopija[d][i])
			{
				kopija[p][i] *= 2;
				kopija[d][i] = 0;
				p--;
			}
			d--;
		}
	}
	for (int i = VEL_MAT - 1; i >= 0; i--)
	{
		int p = VEL_MAT - 1, d = p - 1;
		while (d >= 0 && p >= 0)
		{
			if (kopija[p][i] != 0) p--;
			else if (kopija[p][i] == 0 && kopija[d][i] != 0)
			{
				kopija[p][i] = kopija[d][i];
				kopija[d][i] = 0;
				p--;
			}
			d--;
		}
	}
	if (!isteMatrice(kopija, trenutnoStanje))
	{
		for (int i = 1; i < 9; i++)
		{
			score = evaluacijaPozicije(kopija, i, 0.5);
			noviScore = 0;
			if (dubina != 0)
			{
				c = generisiPoteze(kopija, dubina - 1, maxDubina, baza, &noviScore);
				score += noviScore * pow(baza, maxDubina - dubina + 1);
			}
			if (score > bestScore)
			{
				bestMove = 's';
				bestScore = score;
			}
			score -= noviScore;
		}
		vratiMemoriju(kopija);
	}
	else vratiMemoriju(kopija);
	*scoreBest = bestScore;
	return bestMove;
}
char traziPotez(int** a)
{
	float score = 0;
	char potez = generisiPoteze(a, 2, 2, 0.8, &score);
	return potez;
}