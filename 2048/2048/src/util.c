#include "common.h"

int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (MAX(x1, x2) < MIN(x1 + w1, x2 + w2)) && (MAX(y1, y2) < MIN(y1 + h1, y2 + h2));
} // proveravanje da l su nam se neka dva polja sudarili (koristi se npr. da vidi da l nam je kursor preko buttona)