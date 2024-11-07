#include "common.h"

#define GLYPH_HEIGHT    84
#define GLYPH_WIDTH     48

extern void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y);
extern SDL_Texture* loadTexture(char* filename);