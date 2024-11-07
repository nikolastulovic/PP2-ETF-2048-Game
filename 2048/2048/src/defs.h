#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'
#define PI                   3.14159265358979323846

#define FPS                  60

#define SCREEN_WIDTH         720
#define SCREEN_HEIGHT        900

#define MAX_LINE_LENGTH      1024

#define MAX_NAME_LENGTH      32

#define MAX_SCORE_NAME       4

#define MAX_KEYBOARD_KEYS    350
#define MAX_MOUSE_BUTTONS    6

#define MAX_SND_CHANNELS     5

#define GLYPH_HEIGHT    84
#define GLYPH_WIDTH     48

enum
{
	CH_ANY = -1,
	CH_BLOCK
};

enum
{
	SND_BLOCK,
	SND_MAX
};