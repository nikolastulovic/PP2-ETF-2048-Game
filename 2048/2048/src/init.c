#include "init.h"

void initSDL(void)
{
	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;
	
	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        printf("Couldn't initialize SDL Mixer\n");
		exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS); // alocira nam kanale za zvuk i muziku

	app.window = SDL_CreateWindow("2048!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags); // stvara prozor aplikacije

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags); // Kreiranje renderera
	
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG); // Inicijalizacija koje vrsta fajlova mozemo ucitati kao teksturu
	
	SDL_ShowCursor(0); // 1 - pokazacemo kursor, 0 - necemo

}// Generalna inicijalizacija SDLa

//a-z 58-126
void initHiscore(void) {
	FILE* fajl = fopen("src/hiscore.txt", "r");
	int pozicija = 0;
	int brojac = 0;
	int sig = 0;

	while (pozicija < 10)
	{
		if (brojac < 100)
		{
			char c = fgetc(fajl);
			brojac++;
		}
		else
		{
			if (!sig)
			{
				char a, b, c;
				fscanf(fajl, "%c%c%c", &a, &b, &c);
				pobednici[pozicija].ime[0] = a + 30;
				pobednici[pozicija].ime[1] = b + 30;
				pobednici[pozicija].ime[2] = c + 30;
				sig = 1;
			}
			else
			{
				char c;
				int hi = 0;
				while ((c = fgetc(fajl)) != '`')
				{
					hi = hi * 10 + (c - '0');
				}
				pobednici[pozicija++].hi = hi;
				sig = 0;
			}
			brojac = 0;
		}
	}
	fclose(fajl);
}
//ascii+30->nase slovo pretvoreno u slovo u fajlu
void writeHiscore(void)//SSS 12345124` ali izmedju svakog 100 karaktera random slova
{
	FILE* fajl = fopen("src/hiscore.txt", "w");
	int a = 0;
	int brojac = 0;
	int sig = 0;
	while (a < 10)
	{
		if (brojac < 100)
		{
			int r = 58 + rand() % 68;
			char kar = r;
			fputc(kar, fajl);
			brojac++;
		}
		else
		{
			if (!sig)
			{
				char b, c, d;
				b = pobednici[a].ime[0] - 30;
				c = pobednici[a].ime[1] - 30;
				d = pobednici[a].ime[2] - 30;
				fprintf(fajl, "%c%c%c", b, c, d);
				sig = 1;
			}
			else
			{
				fprintf(fajl, "%d`", pobednici[a++].hi);
				sig = 0;
			}
			brojac = 0;
		}
	}
	fclose(fajl);
}


void initGame(void)
{
	memset(&stage, 0, sizeof(Stage));
	stage.matrix = uzmiMemoriju();//alokacija memorije
	stage.kopija0 = deepCopy(stage.matrix);
	stage.kopija1 = NULL;
	stage.score = 0;//promenljiva za pracenje rezultata
	stage.igraPobedjena = 0;//kada pobedimo igru nema potrebe proveravati ima li 2048 vise
	srand(time(0));//seedovanje randoma da ne bi bile uvek iste igre

	//promenljive za korak u nazad, koja kopija se cuva, i da li je prosli potez bio vracanje, jer se sme vracati samo jednom
	stage.brojKopije = 0;
	stage.vraceno = 0;
	stage.vracenoStaro = 0;

	//inicijalizacija pocetnog stanja
	stage.matrix = generisiRandomElement(stage.matrix, &stage.novii,&stage.novij);
}

void cleanup(void)
{
	
	free(pom);

    writeHiscore();

	vratiMemoriju(stage.matrix);
	if (stage.brojKopije) vratiMemoriju(stage.kopija1);
	else vratiMemoriju(stage.kopija0);

	IMG_Quit();

	SDL_DestroyRenderer(app.renderer);
	
	SDL_DestroyWindow(app.window);
	
	SDL_Quit();
} // kada exitujemo iz programa oslobadjamo se od memorije SDLa i pisemo u fajl hiscore
