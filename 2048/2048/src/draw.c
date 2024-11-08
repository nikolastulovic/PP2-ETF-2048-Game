#include "draw.h"

void prepareScene(void)
{
	SDL_RenderClear(app.renderer);
}

void presentScene(void)
{
	SDL_RenderPresent(app.renderer);
}

SDL_Texture *loadTexture(char *filename)
{
	SDL_Texture *texture;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s ...", filename);
	texture = IMG_LoadTexture(app.renderer, filename);

	return texture;
} // Ucitavanje texture

void blit(SDL_Texture *texture, int x, int y, int center)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	
	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}
	
	SDL_RenderCopy(app.renderer, texture, NULL, &dest);
} // Pomocu blit funkcije stavljamo u nas renderer velicinu i lokaciju nase texture

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y, int small)
{
	SDL_Rect dest;
	
	dest.x = x;
	dest.y = y;
	dest.w = src->w;
	dest.h = src->h;

	if (small) {
		dest.w = dest.w / 2;
		dest.h = dest.h / 2;
	}

	if (small == 4) {
		dest.w = 130;
		dest.h = 130;
	}
	SDL_RenderCopy(app.renderer, texture, src, &dest);
} // Pomocu blit funkcije stavljamo u nas renderer velicinu i lokaciju nase texture (samo sto mozemo da je ogranicimo ili rasirimo)