#include "common.h"

extern int** uzmiMemoriju();
extern int** deepCopy(int** a);
extern int** generisiRandomElement(int** a);
extern void vratiMemoriju(int** a);

Stage stage;
Hiscore pobednici[10];
extern App app;
extern Pomeranja* pom;