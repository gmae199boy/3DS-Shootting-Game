#include "Polygon.h"
#include "number.h"
#include "textureManager.h"


#define NUMBER_CUT_OFFSET_X (0)
#define NUMBER_CUT_OFFSET_Y (80)


static int g_texNum = -1;


void Number_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom://game.tga", 256, 256);
}

void Number_Draw(int n, float x, float y)
{
	if (n < 0 || n > 9) { return; }

	Polygon_Draw(g_texNum,
		x, y,
		NUMBER_CUT_WIDTH, 
		NUMBER_CUT_HEIGHT,
		n * NUMBER_CUT_WIDTH, // êÿÇËéÊÇËç¿ïWx
		NUMBER_CUT_OFFSET_Y,
		NUMBER_CUT_WIDTH,
		NUMBER_CUT_HEIGHT);
}
