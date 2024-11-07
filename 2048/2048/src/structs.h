typedef struct Texture Texture;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

typedef struct {
	int hi;
	char ime[4];
}Hiscore;

typedef struct {
	int x;
	int y;
	int button[MAX_MOUSE_BUTTONS];
} Mouse;

typedef struct {
	int score, score1, score0;
	int** matrix;
	int** kopija0;
	int** kopija1;
	int brojKopije;
	int igraPobedjena;
	int vraceno;
	int vracenoStaro;
	int novii, novij;
	int brojPomeranja;
} Stage;

typedef struct pomeranja
{
	int x1, y1, x2, y2; //pomeranje/spajanje sa x1,y1 na x2,y2
	int spajanje;       //1 spajanje 0 pomeranje
}Pomeranja;

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	char name[MAX_SCORE_NAME];
	char inputText[MAX_LINE_LENGTH];
	Mouse mouse;
} App;
