#include "common.h"

extern void blit(SDL_Texture *texture, int x, int y, int center);
extern void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y);
extern int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
extern SDL_Texture *loadTexture(char *filename);
extern void playMusic(int loop);
extern void playSound(int id, int channel);

extern int postojePotezi(int** a);
extern int** deepCopy(int** a);
extern int** generisiRandomElement(int** a);
extern void vratiMemoriju(int** a);
extern int** unosPoteza(int** a, int** undo, int* score, int* vraceno);
extern char traziPotez(int** a);

extern App app;
extern Stage stage;
extern Pomeranja* pom;
extern Hiscore pobednici[10];