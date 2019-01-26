#include "Polygon.h"
#include "textureManager.h"


#define EXPLOSION_PATTERN_MAX         (8)
#define EXPLOSION_PATTERN_WIDTH_MAX   (4)
#define EXPLOSION_PATTERN_WIDTH       (32)
#define EXPLOSION_PATTERN_WIDTH_HALF  (EXPLOSION_PATTERN_WIDTH / 2)
#define EXPLOSION_PATTERN_HEIGHT      (32)
#define EXPLOSION_PATTERN_HEIGHT_HALF (EXPLOSION_PATTERN_HEIGHT / 2)
#define EXPLOSION_WAIT_FRAME          (10)


static int Explosion_FrameCount = 0;
static int Explosion_BirthFrame = 0;
static float Explosion_PositionX = 0.0f;
static float Explosion_PositionY = 0.0f;
static bool Explosion_Used = false;
static int Explosion_PatternNum = 0;

static int g_texNum = -1;


void Explosion_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom:/explosion.tga", 128, 128);

	Explosion_FrameCount = 0;
	Explosion_BirthFrame = 0;
	Explosion_PositionX = 0.0f;
	Explosion_PositionY = 0.0f;
	Explosion_Used = false;
	Explosion_PatternNum = 0;
}

void Explosion_Update(void)
{
	if( Explosion_Used ) {

		int frame = Explosion_FrameCount
			- Explosion_BirthFrame;

		Explosion_PatternNum = frame
			/ EXPLOSION_WAIT_FRAME;

		if (Explosion_PatternNum >=
			EXPLOSION_PATTERN_MAX) {

			Explosion_Used = false;
		}
	}

	Explosion_FrameCount++;
}

void Explosion_Draw(void)
{
	if( !Explosion_Used ) {
		return;
	}

	int x = (Explosion_PatternNum 
		% EXPLOSION_PATTERN_WIDTH_MAX) 
		* EXPLOSION_PATTERN_WIDTH;
	int y = (Explosion_PatternNum
		/ EXPLOSION_PATTERN_WIDTH_MAX)
		* EXPLOSION_PATTERN_HEIGHT;

	Polygon_Draw(g_texNum,
		Explosion_PositionX - EXPLOSION_PATTERN_WIDTH_HALF,
		Explosion_PositionY - EXPLOSION_PATTERN_HEIGHT_HALF,
		EXPLOSION_PATTERN_WIDTH, 
		EXPLOSION_PATTERN_HEIGHT,
		x,
		y,
		EXPLOSION_PATTERN_WIDTH,
		EXPLOSION_PATTERN_HEIGHT);
}

void Explosion_Create(float x, float y)
{
	if (!Explosion_Used) {

		Explosion_BirthFrame = Explosion_FrameCount;
		Explosion_PositionX = x;
		Explosion_PositionY = y;
		Explosion_Used = true;
	}
}
