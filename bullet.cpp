#include "Polygon.h"
#include "collision.h"
#include "bullet.h"
#include "textureManager.h"


#define BULLET_WIDTH         (6)                // �v���C���[�摜�̕�
#define BULLET_HEIGHT        (24)                // �v���C���[�摜�̍���
#define BULLET_WIDTH_HALF    (BULLET_WIDTH  / 2) // �v���C���[�摜�̕��̔���
#define BULLET_HEIGHT_HALF   (BULLET_HEIGHT / 2) // �v���C���[�摜�̍����̔���
#define BULLET_TEXTURE_CUT_X (52)
#define BULLET_TEXTURE_CUT_Y (0)
#define BULLET_COLLISION_CIRCLE_RADIUS (BULLET_WIDTH_HALF)

#define BULLET_SPEED_X ( 0.0f)
#define BULLET_SPEED_Y (-8.0f)

// �e�\����
typedef struct Bullet_tag
{
	float PositionX;
	float PositionY;
	float SpeedX;
	float SpeedY;
	bool Used;
	Circle Collision;
}Bullet;

static Bullet Bullets[BULLET_COUNT_MAX];

static int g_texNum = -1;


void Bullet_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom://game.tga", 256, 256);

	for (int i = 0; i < BULLET_COUNT_MAX; i++) {
		Bullets[i].Used = false;
	}
}

void Bullet_Update(void)
{
	for (int i = 0; i < BULLET_COUNT_MAX; i++) {

		if (!Bullets[i].Used) {
			continue;
		}

		Bullets[i].PositionX += Bullets[i].SpeedX;
		Bullets[i].PositionY += Bullets[i].SpeedY;
		Bullets[i].Collision.cx = Bullets[i].PositionX;
		Bullets[i].Collision.cy = Bullets[i].PositionY - 8;

		// ��ʂ̊O�ɏo����
		if (Bullets[i].PositionY + BULLET_HEIGHT < 0) {

			Bullets[i].Used = false;
		}
	}
}

void Bullet_Draw(void)
{
	for (int i = 0; i < BULLET_COUNT_MAX; i++) {
		
		if (!Bullets[i].Used) {
			continue;
		}

		Polygon_Draw(g_texNum,
			Bullets[i].PositionX - BULLET_WIDTH_HALF,
			Bullets[i].PositionY - BULLET_HEIGHT_HALF,
			BULLET_WIDTH, BULLET_HEIGHT,
			BULLET_TEXTURE_CUT_X,
			BULLET_TEXTURE_CUT_Y,
			BULLET_WIDTH, BULLET_HEIGHT);
	}
}

void Bullet_Create(float x, float y)
{
	for (int i = 0; i < BULLET_COUNT_MAX; i++) {
		// �g���Ă��Ȃ��f�[�^��T��
		if (Bullets[i].Used) {
			continue; // �l�Y�~�Ԃ�
		}
		// �� �g���Ă��Ȃ��f�[�^����
		Bullets[i].Used = true;
		Bullets[i].PositionX = x;
		Bullets[i].PositionY = y;
		Bullets[i].SpeedX = BULLET_SPEED_X;
		Bullets[i].SpeedY = BULLET_SPEED_Y;
		Bullets[i].Collision.cx = x;
		Bullets[i].Collision.cy = y 
			- BULLET_HEIGHT_HALF;
		Bullets[i].Collision.radius 
			= BULLET_COLLISION_CIRCLE_RADIUS;
		break;
	}
}

// �e�̓����蔻����擾����
const Circle* Bullet_GetCollision(int index)
{
	return &Bullets[index].Collision;
}

// �e�𖳌��ɂ���
void Bullet_Destroy(int index)
{
	Bullets[index].Used = false;
}

// �e���L�����擾����
bool Bullet_IsEnable(int index)
{
	return Bullets[index].Used;
}
