#include "Polygon.h"
#include "collision.h"
#include "textureManager.h"


#define ENEMY_WIDTH         (32)               
#define ENEMY_HEIGHT        (32)              
#define ENEMY_WIDTH_HALF    (ENEMY_WIDTH  / 2)
#define ENEMY_HEIGHT_HALF   (ENEMY_HEIGHT / 2)
#define ENEMY_TEXTURE_CUT_X (0)
#define ENEMY_TEXTURE_CUT_Y (48)
#define ENEMY_COLLISION_CIRCLE_RADIUS (ENEMY_WIDTH_HALF)

#define ENEMY_SPEED_X (-1.0f)
#define ENEMY_SPEED_Y ( 0.0f)

static float Enemy_PositionX = 0.0f;
static float Enemy_PositionY = 0.0f;
static float Enemy_SpeedX = 0.0f;
static float Enemy_SpeedY = 0.0f;
static bool Enemy_Used = false;
static Circle Enemy_Collision;

static int g_texNum = -1;


void Enemy_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom://game.tga", 256, 256);

	Enemy_PositionX = 0.0f;
	Enemy_PositionY = 0.0f;
	Enemy_SpeedX = 0.0f;
	Enemy_SpeedY = 0.0f;
	Enemy_Used = false;
	Enemy_Collision.cx = Enemy_PositionX;
	Enemy_Collision.cy = Enemy_PositionY;
	Enemy_Collision.radius 
		= ENEMY_COLLISION_CIRCLE_RADIUS;
}

void Enemy_Update(void)
{
	if (Enemy_Used) {

		Enemy_PositionX += Enemy_SpeedX;
		Enemy_PositionY += Enemy_SpeedY;
		Enemy_Collision.cx = Enemy_PositionX;
		Enemy_Collision.cy = Enemy_PositionY;

		// âÊñ ÇÃäOÇ…èoÇΩÇÁ
		if( Enemy_PositionX + ENEMY_WIDTH < 0) {
			
			Enemy_Used = false;
		}
	}
}

void Enemy_Draw(void)
{
	if (!Enemy_Used) {
		return;
	}

	Polygon_Draw(g_texNum,
		Enemy_PositionX - ENEMY_WIDTH_HALF,
		Enemy_PositionY - ENEMY_HEIGHT_HALF,
		ENEMY_WIDTH, ENEMY_HEIGHT,
		ENEMY_TEXTURE_CUT_X,
		ENEMY_TEXTURE_CUT_Y,
		ENEMY_WIDTH, ENEMY_HEIGHT);
}

void Enemy_Create(float x, float y)
{
	if (Enemy_Used) {
		// Ç∑Ç≈Ç…égÇÌÇÍÇƒÇ¢ÇΩÇÁ
		return; // âΩÇ‡ÇµÇ»Ç¢
	}

	Enemy_Used = true; // ìGÇégópíÜÇ…Ç∑ÇÈ
	Enemy_PositionX = x;
	Enemy_PositionY = y;
	Enemy_SpeedX = ENEMY_SPEED_X;
	Enemy_SpeedY = ENEMY_SPEED_Y;
}

// ìGÇÃìñÇΩÇËîªíËÇéÊìæÇ∑ÇÈ
const Circle* Enemy_GetCollision(void)
{
	return &Enemy_Collision;
}

// ìGÇñ≥å¯Ç…Ç∑ÇÈ
void Enemy_Destroy(void)
{
	Enemy_Used = false;
}

bool Enemy_IsEnable(void)
{
	return Enemy_Used;
}