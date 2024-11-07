#include "stage.h"

static void logic(void);
static void draw(void);
//logika igrice
static void doBackground(void);
static void doGame(void);
//dugmici logika
static void doHiToHome(void);
static void moveHiscore(int pozicija);
static void doNameInput(int pozicija);
static void doButtons(void);
static void doOptionButtons(void);
static void do4Buttons(void);
static void doInfoButton(void);
//grafika igrice
static void drawInfoBorder(void);
static void drawInfoText(void);
static void drawInfoScreen(void);
static void drawHiToHome(void);
static void drawHiscoreborder(void);
static void drawHiscores(void);
static void drawNameInput(void);
static void drawMouse(void);
static void draw4Buttons(void);
static void drawInfoButton(void);
static void drawOptionButtons(void);
static void drawGrid(void);
static void drawBackground(void);
static void drawButtons(void);
static void drawTitle(void);
static void drawBorder(void);
static void drawHud(void);
static void drawBlock(int i, int j, int val);
static void drawGame(void);
static void drawOverScreen(void);
static void drawNewBlock(int i, int j, int val);
static void animateBlock(int i, int j, int val);

static SDL_Texture *targetterTexture;
static SDL_Texture* background[2];
static SDL_Texture* start[2];
static SDL_Texture* options[2];
static SDL_Texture* hiscore[2];
static SDL_Texture* quit[2];
static SDL_Texture* hint[2];
static SDL_Texture* back[2];
static SDL_Texture* home[2];
static SDL_Texture* reset[2];
static SDL_Texture* info[2];
static SDL_Texture* soundonoff[4];
static SDL_Texture* dayornight[4];

static SDL_Texture* title[2];
static SDL_Texture* border;
static SDL_Texture* creditborder;
static SDL_Texture* grid;
static SDL_Texture* gameover;
static SDL_Texture* congrats;
static SDL_Texture* blocks[13];

//neke promenljive
static int moveTitle;
static int scene;
static int popup;
static int animate;
static int gameon = 0;
static int pressed;
static int backgroundY;
static int nofirstmove;
static int hearing;
static int winner;
static int novihiscore;
static int cursorBlink;
static int theme;

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;
	title[0] = loadTexture("gfx/title.png");
	background[0] = loadTexture("gfx/background.png");
	title[1] = loadTexture("gfx/nighttitle.png");
	background[1] = loadTexture("gfx/nightbackground.png");
	targetterTexture = loadTexture("gfx/cursor.png");
	border = loadTexture("gfx/border.png");
	grid = loadTexture("gfx/grid.png");
	gameover = loadTexture("gfx/gameover.png");
	congrats = loadTexture("gfx/congrats.png");
	creditborder = loadTexture("gfx/creditborder.png");
	// Texture koje ce biti koriscene se ucitavaju ovde u promenljive
	// Prvo buttoni
	start[0] = loadTexture("gfx/playbutton.png");
	start[1] = loadTexture("gfx/playbuttonpressed.png");
	quit[0] = loadTexture("gfx/quitbutton.png");
	quit[1] = loadTexture("gfx/quitbuttonpressed.png");
	options[0] = loadTexture("gfx/optionsbutton.png");
	options[1] = loadTexture("gfx/optionsbuttonpressed.png");
	hiscore[0] = loadTexture("gfx/hiscorebutton.png");
	hiscore[1] = loadTexture("gfx/hiscorebuttonpressed.png");
	hint[0] = loadTexture("gfx/hintbutton.png");
	hint[1] = loadTexture("gfx/hintbuttonpressed.png");
	back[0] = loadTexture("gfx/backbutton.png");
	back[1] = loadTexture("gfx/backbuttonpressed.png");
	home[0] = loadTexture("gfx/homebutton.png");
	home[1] = loadTexture("gfx/homebuttonpressed.png");
	reset[0] = loadTexture("gfx/resetbutton.png");
	reset[1] = loadTexture("gfx/resetbuttonpressed.png");
	soundonoff[2] = loadTexture("gfx/soundonbutton.png");
	soundonoff[3] = loadTexture("gfx/soundonbuttonpressed.png");
	soundonoff[0] = loadTexture("gfx/soundoffbutton.png");
	soundonoff[1] = loadTexture("gfx/soundonbuttonpressed.png");
	info[0] = loadTexture("gfx/infobutton.png");
	info[1] = loadTexture("gfx/infobuttonpressed.png");
	dayornight[0] = loadTexture("gfx/sunbutton.png");
	dayornight[1] = loadTexture("gfx/sunbuttonpressed.png");
	dayornight[2] = loadTexture("gfx/moonbutton.png");
	dayornight[3] = loadTexture("gfx/moonbuttonpressed.png");
	//Sada teksture kockica
	blocks[1] = loadTexture("gfx/2.png");
	blocks[2] = loadTexture("gfx/4.png");
	blocks[3] = loadTexture("gfx/8.png");
	blocks[4] = loadTexture("gfx/16.png");
	blocks[5] = loadTexture("gfx/32.png");
	blocks[6] = loadTexture("gfx/64.png");
	blocks[7] = loadTexture("gfx/128.png");
	blocks[8] = loadTexture("gfx/256.png");
	blocks[9] = loadTexture("gfx/512.png");
	blocks[10] = loadTexture("gfx/1024.png");
	blocks[11] = loadTexture("gfx/2048.png");
	blocks[12] = loadTexture("gfx/4096.png");

	loadMusic("music/igrica.mp3"); //ucita se mp3 fajl
	playMusic(1); //pusti se mp3 fajl

	// neke promenljive koje cemo koristiti tokom programa
	popup = 0; // sluzi za animiranje novih kockica
	animate = 0; // sluzi za animiranje tojest pomeranje kockica
	pressed = 0; // gleda da li je stisnut neki button
	scene = 0; // Pomocu ove promeljive saznajemo sta crtamo
	moveTitle = 10; // koristi se za pomeranje titla kad prvi put zapocnemo play
	nofirstmove = 1; // da znamo da li je igrac odigrao prvi potez
	hearing = 1; // sluzi u opcijama prepoznamo da li je muzika ukljucena ili iskljucena
	novihiscore = 0; // da li je korisnik pobedio
	theme = 0; // dark theme ili light theme
}

static void logic(void)
{
	doBackground();

	if (scene == 0) doButtons();

	if ((scene == 1 || scene == 10) && !novihiscore) do4Buttons();

	if (scene == 2) doOptionButtons();

	if (scene != 1 && scene != 10) doInfoButton();

	if (gameon) doGame();

	if (scene == 10) {
		int i;
		if (novihiscore) {

			for (i = 9; i != -1; i--)
			{
				if (stage.score < pobednici[i].hi) break;
			}
			i++;
			winner = i;
			if (stage.score != pobednici[i].hi) moveHiscore(i);
			pobednici[i].hi = stage.score;

			doNameInput(i);
		}
	}
	if (scene == 3 || scene == 2 || scene == 4) doHiToHome();

	if (!app.mouse.button[SDL_BUTTON_LEFT] && pressed) pressed = 0;
}

static void moveHiscore(int pozicija) {
	int i;
	for ( i = 9; i != pozicija; i--)
	{
		pobednici[i].hi = pobednici[i - 1].hi;
		STRNCPY(pobednici[i].ime, pobednici[i - 1].ime, MAX_SCORE_NAME);
	}
	pobednici[pozicija].ime[0] = '\0';
}

static void doNameInput(int pozicija)
{
	int i, n;
	char c;

	n = strlen(pobednici[pozicija].ime);

	for (i = 0; i < strlen(app.inputText); i++)
	{
		c = toupper(app.inputText[i]);

		if (n < MAX_SCORE_NAME - 1 && c >= ' ' && c <= 'Z')
		{
			pobednici[pozicija].ime[n++] = c;
		}
	}

	if (n > 0 && app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		pobednici[pozicija].ime[--n] = '\0';

		app.keyboard[SDL_SCANCODE_BACKSPACE] = 0;
	}

	if (app.keyboard[SDL_SCANCODE_RETURN])
	{
		if (strlen(pobednici[pozicija].ime) != 3)
		{
			STRNCPY(pobednici[pozicija].ime, "NAN", MAX_SCORE_NAME);
		}
		novihiscore = 0;
		scene = 0;
		app.keyboard[SDL_SCANCODE_R] = 1;
	}
}

static void doGame(void) {
	if (novihiscore)return;
	if (scene != 1 && scene != 10)return;
	if (!postojePotezi(stage.matrix)) scene = 10;
	else scene = 1;
	if (nofirstmove && app.keyboard[SDL_SCANCODE_B]) app.keyboard[SDL_SCANCODE_B] = 0;
	if ((!app.keyboard[SDL_SCANCODE_UP] && !app.keyboard[SDL_SCANCODE_DOWN] && !app.keyboard[SDL_SCANCODE_LEFT] && !app.keyboard[SDL_SCANCODE_RIGHT] && !app.keyboard[SDL_SCANCODE_B] && !app.keyboard[SDL_SCANCODE_R] && !app.keyboard[SDL_SCANCODE_H]) || popup || animate) return;
	if (!stage.brojKopije)//regulisanje starog stanja i njegovo cuvanje za eventualno vracanje na korak u nazad, pokretanje funkcija za novi potez
	{
		stage.kopija1 = deepCopy(stage.matrix);
		stage.score1 = stage.score;
		stage.vracenoStaro = stage.vraceno;
		stage.matrix = unosPoteza(stage.matrix, stage.kopija0, &stage.score, &stage.vraceno, stage.score0);//za undo treba undo i scora
		if (isteMatrice(stage.matrix, stage.kopija1)) {
			vratiMemoriju(stage.kopija1);
			return;
		}
		if (stage.vraceno == stage.vracenoStaro) stage.vraceno = 0;
		stage.matrix = deepCopy(stage.matrix);
		if (!(isteMatrice(stage.matrix, stage.kopija1)) && stage.vraceno < 2 && !app.keyboard[SDL_SCANCODE_B]) stage.matrix = generisiRandomElement(stage.matrix, &stage.novii, &stage.novij);
		vratiMemoriju(stage.kopija0);
		stage.brojKopije = 1;
	}
	else
	{
		stage.kopija0 = deepCopy(stage.matrix);
		stage.score0 = stage.score;
		stage.vracenoStaro = stage.vraceno;
		stage.matrix = unosPoteza(stage.matrix, stage.kopija1, &stage.score, &stage.vraceno, stage.score1);
		if (isteMatrice(stage.matrix, stage.kopija0)) {
			vratiMemoriju(stage.kopija0);
			return;
		}
		if (stage.vraceno == stage.vracenoStaro) stage.vraceno = 0;
		stage.matrix = deepCopy(stage.matrix);
		if (!(isteMatrice(stage.matrix, stage.kopija1)) && stage.vraceno < 2) stage.matrix = generisiRandomElement(stage.matrix,&stage.novii,&stage.novij);
		vratiMemoriju(stage.kopija1);
		stage.brojKopije = 0;
	}
	if (!stage.igraPobedjena && pobeda(stage.matrix)) stage.igraPobedjena = 1;//provera pobede
	nofirstmove = 0;
	if (app.keyboard[SDL_SCANCODE_R]) nofirstmove = 1;
	app.keyboard[SDL_SCANCODE_UP] = 0;
	app.keyboard[SDL_SCANCODE_DOWN] = 0;
	app.keyboard[SDL_SCANCODE_LEFT] = 0;
	app.keyboard[SDL_SCANCODE_RIGHT] = 0;
	app.keyboard[SDL_SCANCODE_B] = 0;
	app.keyboard[SDL_SCANCODE_R] = 0;
	app.keyboard[SDL_SCANCODE_H] = 0;
	popup = 10;
	playSound(SND_BLOCK, CH_BLOCK);
	animate = 10; 
	if (!postojePotezi(stage.matrix)) { //provera da li postoji moguc potez i ako ne postoji sledi sekvenca za kraj igre
		scene = 10;
		if (stage.score > pobednici[9].hi) novihiscore = 1;
	}
}

static void doBackground(void) {
	if (--backgroundY < -SCREEN_HEIGHT) backgroundY = 0;
}


// Generalna logika za buttone
//////////////////////////////
static void doInfoButton(void) {
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, 20, SCREEN_HEIGHT - 120, 98, 108) && pressed) {
		scene = 4;
		pressed = 0;
	}
}

static void doHiToHome(void) {
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, 20, SCREEN_HEIGHT - 240, 98, 108) && pressed){
		scene = 0;
		pressed = 0;
	}
}

static void doOptionButtons(void) {
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 98, 108) && pressed) {
		theme = !theme;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 98, 108) && pressed) {
		hearing = !hearing;
		if (hearing)Mix_ResumeMusic();
		else Mix_PauseMusic();
		pressed = 0;
	}
}

static void doButtons(void) {

	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 - 60 - 54, 222, 108) && pressed) {
		scene = 1;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 + 60 - 54, 222, 108) && pressed) {
		scene = 2;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 +180 - 54, 222, 108) && pressed) {
		scene = 3;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 + 300 - 54, 222, 108) && pressed) {
		exit(0);
	}
}

static void do4Buttons(void) {
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250, 180, 98, 108) && pressed) {
		app.keyboard[SDL_SCANCODE_B] = 1;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250 + 105, 180, 98, 108) && pressed) {
		app.keyboard[SDL_SCANCODE_H] = 1;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250, 65, 98, 108) && pressed) {
		scene = 0;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250 + 105, 65, 98, 108) && pressed) {
		app.keyboard[SDL_SCANCODE_R] = 1;
		pressed = 0;
	}
	if (!app.mouse.button[SDL_BUTTON_LEFT] && pressed) pressed = 0;
}
//////////////////////////////

// gledajuci vrednost scene biramo sta crtamo pomocu ove funkcije
static void draw(void)
{
	drawBackground();

	if (scene == 0) {
		drawTitle();
		drawButtons();
		moveTitle = 10;
	}

	if ((scene == 1 || scene == 10) && moveTitle) {
		blit(title[theme], 0 + 13 * moveTitle, 20, 0);
		moveTitle--;
	}

	if ((scene == 1 || scene == 10) && !moveTitle) {
		blit(title[theme], 0, 20, 0);
		drawHud();
		draw4Buttons();
		drawGame();
		drawGrid();
		drawBorder();
		if (scene == 10) {
			drawOverScreen();
			if (novihiscore) {
				drawNameInput();
			}
			if (++cursorBlink >= FPS)
			{
				cursorBlink = 0;
			}
		}
	}

	if (scene == 2) {
		drawTitle();
		drawOptionButtons();
		drawHiToHome();
	}

	if (scene == 3) {
		drawTitle();
		drawHiToHome();
		drawHiscores();
		drawHiscoreborder();
	}

	if (scene == 4) {
		drawHiToHome();
		drawInfoText();
		drawInfoScreen();
		drawInfoBorder();
	}

	if (scene != 1 && scene != 10) {
		drawInfoButton();
	}
	drawMouse();
}

// crtanje bordera za info
static void drawInfoBorder(void) {
	SDL_Rect src , rrc;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(creditborder, NULL, NULL, &src.w, &src.h);
	src.w = 550;
	src.h;
	blitRect(creditborder, &src, 140, 620, 0);
	src.w = 700;
	src.h = 400;
	blitRect(creditborder, &src, 10, 15, 0);
}

// crtanje infotext
static void drawInfoText(void) {
	drawText(20, 60, 255, 255, 255, "............INFO............");
	drawText(20, 100, 255, 255, 255, "............................");
	drawText(20, 140, 255, 255, 255, "............................");
	drawText(20, 180, 255, 255, 255, "............................");
	drawText(20, 220, 255, 255, 255, "............................");
	drawText(20, 260, 255, 255, 255, "............................");
	drawText(20, 300, 255, 255, 255, "............................");
	drawText(20, 340, 255, 255, 255, "............................");
	drawText(30, 110, 255, 255, 255, ".......HOME.................");
	drawText(30, 210, 255, 255, 255, ".......BACK.................");
	drawText(30, 310, 255, 255, 255, ".......THEME................");
	drawText(540, 110, 255, 255, 255, "HINT");
	drawText(540, 210, 255, 255, 255, "RESET");
	drawText(540, 310, 255, 255, 255, "SOUND");

	drawText(-10, 440, 255, 255, 255, ".USE.ARROW.KEYS.TO.MOVE.BLOCKS.");
	drawText(-10, 480, 255, 255, 255, "...COMBINE.THEM.TO.GAIN.SCORE...");
	drawText(-10, 520, 255, 255, 255, "....CAN.YOU.MAKE.IT.TO.2048?....");

	drawText(153, 650, 255, 255, 255, ".CREATED.WITH.LOVE.BY");
	drawText(153, 690, 255, 255, 255, ".....................");
	drawText(153, 700, 255, 255, 255, ".....................");
	drawText(150, 740, 255, 255, 255, "....NIKOLA.STULOVIC...");
	drawText(150, 780, 255, 255, 255, "..........AND.........");
	drawText(150, 820, 255, 255, 255, "....MATEJA.PAVLOVIC...");
}

//crtanje info screena
static void drawInfoScreen(void) {
	blit(home[1], 80, 70 , 0);
	blit(back[1], 80, 170, 0);
	blit(dayornight[1], 80, 270, 0);
	blit(hint[1], 420, 70, 0);
	blit(reset[1], 420, 170 , 0);
	blit(soundonoff[3], 420, 270, 0);
}
//button koji vraca u meni
static void drawHiToHome(void) {
	int clicked = 0;
	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, 20, SCREEN_HEIGHT - 240, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(home[clicked], 20, SCREEN_HEIGHT - 240 + clicked * 12, 0);
	clicked = 0;
}

//ispisuje se border koji sadrzi hiscorove
static void drawHiscoreborder(void) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(border, NULL, NULL, &src.w, &src.h);
	src.w += 38;
	src.h += 78;
	blitRect(border, &src, 140, 280, 0);
}

// ispis hiscore screena
static void drawHiscores(void)
{
	int i, y;

	y = 350;

	drawText(160, 310, 255, 255, 255, ".......HISCORES......");

	for (i = 0; i < 10; i++)
	{
		drawText(160, y, 255, 255, 255, "#%02d..%-3s......%06d.", (i + 1), pobednici[i].ime, pobednici[i].hi);
		if (i != 9) drawText(160, y + GLYPH_HEIGHT / 2 , 255, 255, 255, ".....................");
		y += 50;
	}
}

// kad se upisuje ime
static void drawNameInput(void)
{
	SDL_Rect r;

	drawText(120, 615, 255, 255, 255, "ENTER-YOUR-NAME--");

	drawText(500, 615, 255, 255, 255, pobednici[winner].ime);

	if (cursorBlink < FPS / 2)
	{
		r.x = (500 + (strlen(pobednici[winner].ime) * GLYPH_WIDTH) / 2) + 5;
		r.y = 615;
		r.w = GLYPH_WIDTH / 2;
		r.h = GLYPH_HEIGHT / 2;

		SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(app.renderer, &r);
	}
}
//Kad se izgubi igra ova funkcija se poziva i na osnovu skora ona crta "game over" ili "congrats"
static void drawOverScreen(void) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(border, NULL, NULL, &src.w, &src.h);
	src.w += 42;
	src.h += 42;
	if (stage.score > pobednici[9].hi) blitRect(congrats, &src, 80, 300, 0);
	else blitRect(gameover, &src, 80, 300, 0);
}
// Crtanje naseg unikatnog kursora na lokaciju misa
static void drawMouse(void) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(targetterTexture, NULL, NULL, &src.w, &src.h);
	src.w += 9;
	src.h += 11;
	blitRect(targetterTexture, &src, app.mouse.x, app.mouse.y, 0);
}
// info button koji se nalazi skoro u svakoj sceni
static void drawInfoButton(void) {
	int clicked = 0;
	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, 20, SCREEN_HEIGHT - 120, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(info[clicked], 20 , SCREEN_HEIGHT - 120 + clicked * 12, 0);
	clicked = 0;
}
// buttoni za opcije
static void drawOptionButtons(void) {
	int clicked = 0;
	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(dayornight[clicked + theme * 2], SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + clicked * 12, 0);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(soundonoff[clicked + hearing * 2], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + clicked * 12, 0);
	clicked = 0;
}
//crtanje game buttona(home,hint,back,reset) kada se udje u igru
static void draw4Buttons(void) {
	int clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250, 180, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(back[clicked], SCREEN_WIDTH - 250, 180 + clicked * 12, 0);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250 + 105, 180, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(hint[clicked], SCREEN_WIDTH - 250 + 105, 180 + clicked * 12, 0);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250, 65, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(home[clicked], SCREEN_WIDTH - 250, 65 + clicked * 12, 0);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH - 250 + 105, 65, 98, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(reset[clicked], SCREEN_WIDTH - 250 + 105, 65 + clicked * 12, 0);
	clicked = 0;
}

// Ovde je crtanje menu buttona
static void drawButtons(void) {
	int clicked = 0;
	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 - 60 - 54, 222, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(start[clicked], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60 + clicked * 12, 1);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 + 60 - 54, 222, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(options[clicked], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60 + clicked * 12, 1);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 + 180 - 54, 222, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(hiscore[clicked], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 180 + clicked * 12, 1);
	clicked = 0;

	if (app.mouse.button[SDL_BUTTON_LEFT] && collision(app.mouse.x, app.mouse.y, 3, 3, SCREEN_WIDTH / 2 - 111, SCREEN_HEIGHT / 2 + 300 - 54, 222, 108)) {
		clicked = 1;
		pressed = 1;
	}
	blit(quit[clicked], SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300 + clicked * 12, 1);
}

// jednostavno crtanje Title.png pomocu blit funkcije
static void drawTitle(void) {
	blit(title[theme], 130, 20, 0);
}

//prostor gde se igra igra
static void drawBorder(void) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(border, NULL, NULL, &src.w, &src.h);
	src.w += 42;
	src.h += 42;
	blitRect(border, &src, 80, 300, 0);
}

//jednostavno koriscenjem grafike grid crtamo male pluseve koji ce nam razdvajati blockove
static void drawGrid(void) {
	int i, j;
	for ( i = 0; i < 4; i++)
	{
		if (i == 3) continue;
		for ( j = 0; j < 4; j++)
		{
			if (j == 3) continue;
			SDL_Rect src;
			src.x = 0;
			src.y = 0;
			SDL_QueryTexture(grid, NULL, NULL, &src.w, &src.h);

			SDL_Rect dest;

			dest.x = 100 + 130 * j;
			dest.y = 320 + 130 * i;
			dest.w = 260;
			dest.h = 260;
			SDL_RenderCopy(app.renderer, grid, NULL, &dest);
		}
	}
}
//crtamo background i pomocu y ga nadovezemo da izgleda kao da png fajl nema kraj
static void drawBackground(void)
{
	SDL_Rect dest;
	int y;
	for (y = backgroundY; y < SCREEN_HEIGHT; y += SCREEN_HEIGHT)
	{
		dest.x = 0;
		dest.y = y;
		dest.w = SCREEN_WIDTH;
		dest.h = SCREEN_HEIGHT;
		SDL_RenderCopy(app.renderer, background[theme], NULL, &dest);
	}
}

//Generalno neka logika kad se koji block crta i gde. Da li ce biti popup animacija, move animacija, ili staticki block
static void drawGame(void)
{
	int i, j, k, val = 0, uk =0;
	int **crtaj;
	if (stage.brojKopije) crtaj = stage.kopija1;
	else crtaj = stage.kopija0;
	for ( i = 0; i < 4; i++)
	{
		if (animate) {
			for (j = 0; j < 4; j++)
			{
				while (crtaj[i][j] != 0) {
					val = 1;
					if (crtaj[i][j] == 2) {
						break;
					}
					while (1) {
						uk = 1;
						for (k = 0; k < val; k++)
						{
							uk *= 2;
						}
						if (crtaj[i][j] / uk == 1) break;
						val++;
					}
					break;
				}
				animateBlock(i, j, val);
				val = 0;
			}
		}
		else {
			for (j = 0; j < 4; j++)
			{
				while (stage.matrix[i][j] != 0) {
					val = 1;
					if (stage.matrix[i][j] == 2) {
						break;
					}
					while (1) {
						uk = 1;
						for (k = 0; k < val; k++)
						{
							uk *= 2;
						}
						if (stage.matrix[i][j] / uk == 1) break;
						val++;
					}
					break;
				}
				if (i == stage.novii && j == stage.novij) drawNewBlock(i, j, val);

				else drawBlock(i, j, val);
				val = 0;
			}
		}
	}
	if (animate) animate--;
	gameon = 1;
}
// Animacija blocka kada korisnik uradi potez
static void animateBlock(int i, int j, int val) {
	int brP=-1;

	for (int t = 0; t < stage.brojPomeranja; t++)
	{
		if (pom[t].x1 == i && pom[t].y1 == j)
		{
			brP = t;
			break;
		}
	}
	int animacijax, animacijay;
	if (brP == -1) {
		animacijax = 0;
		animacijay = 0;
	}
	else {
		animacijay = pom[brP].x2 - pom[brP].x1;
		animacijax = pom[brP].y2 - pom[brP].y1;
	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(blocks[val], NULL, NULL, &src.w, &src.h);

	SDL_Rect dest;

	dest.x = 100 + 130 * j + animacijax * 130 - animacijax * 13 * animate;
	dest.y = 320 + 130 * i + animacijay * 130 - animacijay * 13 * animate;
	dest.w = 130;
	dest.h = 130;
	SDL_RenderCopy(app.renderer, blocks[val], NULL, &dest);
}
// dok popup nije nula ovde crtamo manji block pa ga sve povecavamo dok ne dodje to finalne velicine (kad je popup = 0) 
static void drawNewBlock(int i, int j, int val) {
	if (popup == 0) {
		drawBlock(i, j, val);
		return;
	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(blocks[val], NULL, NULL, &src.w, &src.h);

	SDL_Rect dest;

	dest.x = 100 + 130 * j + 6.5 * popup;
	dest.y = 320 + 130 * i + 6.5 * popup;
	dest.w = 130 - 13 * popup;
	dest.h = 130 - 13 * popup;
	SDL_RenderCopy(app.renderer, blocks[val], NULL, &dest);
	popup--;
}
//crtanje blocka u gridu dok igrac ne igra potez
static void drawBlock(int i, int j, int val) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(blocks[val], NULL, NULL, &src.w, &src.h);
	blitRect(blocks[val], &src, 100 + 130 * j, 320 + 130 * i, 4);
}

static void drawHud(void)
{
	drawText(104, 263, 255, 255, 255, "-SCORE-%06d-", stage.score);
}
