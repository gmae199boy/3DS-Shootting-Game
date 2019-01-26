#include "nn/math.h"
#include "Polygon.h"
#include "main.h"
#include "bullet.h"
#include "textureManager.h"


#define PLAYER_SPEED         (0.1f)              // �v���C���[�̑���
#define PLAYER_WIDTH         (48)                // �v���C���[�摜�̕�
#define PLAYER_HEIGHT        (48)                // �v���C���[�摜�̍���
#define PLAYER_WIDTH_HALF    (PLAYER_WIDTH  / 2) // �v���C���[�摜�̕��̔���
#define PLAYER_HEIGHT_HALF   (PLAYER_HEIGHT / 2) // �v���C���[�摜�̍����̔���
#define PLAYER_TEXTURE_CUT_X (0)
#define PLAYER_TEXTURE_CUT_Y (0)


// �v���C���[�̒��S���W
static float Player_PositionX = 0.0f;
static float Player_PositionY = 0.0f;

// �v���C���[�̑��x
static float Player_SpeedX = 0.0f;
static float Player_SpeedY = 0.0f;

static int g_texNum = -1;


// �v���C���[�̏�����
void Player_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom://game.tga", 256, 256);

	Player_PositionX = SCREEN_0_WIDTH * 0.5f;
	Player_PositionY = SCREEN_0_HEIGHT - PLAYER_HEIGHT * 2.0f;
	Player_SpeedX = 0.0f;
	Player_SpeedY = 0.0f;
}

// �v���C���[�̈ړ�
void Player_MoveFront(void)
{
	// Player_PositionY -= PLAYER_SPEED;
	Player_SpeedY -= PLAYER_SPEED;
}

void Player_MoveRight(void)
{
	// Player_PositionX += PLAYER_SPEED;
	Player_SpeedX += PLAYER_SPEED;
}

void Player_MoveLeft(void)
{
	// Player_PositionX -= PLAYER_SPEED;
	Player_SpeedX -= PLAYER_SPEED;
}

void Player_MoveBack(void)
{
	// Player_PositionY += PLAYER_SPEED;
	Player_SpeedY += PLAYER_SPEED;
}

/*
void Player_Move(const nn::math::VEC2* pV)
{
	
}
*/

void Player_Shot(void)
{
	Bullet_Create(
		Player_PositionX, 
		Player_PositionY - PLAYER_HEIGHT_HALF);
}

// �v���C���[�̍X�V
void Player_Update(void)
{
	Player_PositionX += Player_SpeedX;
	Player_PositionY += Player_SpeedY;
	Player_SpeedX *= 0.98f;
	Player_SpeedY *= 0.98f;

	// ��ʂ̊O�ɏo�Ă����Ȃ��悤�ɗ}������
	if (Player_PositionX < 0.0f) {
		Player_PositionX = 0.0f;
		Player_SpeedX = 0.0f;
	}

	if (Player_PositionX > SCREEN_0_WIDTH - PLAYER_WIDTH) {
		Player_PositionX = SCREEN_0_WIDTH - PLAYER_WIDTH;
	}
}

// �v���C���[�̕`��
void Player_Draw(void)
{
	Polygon_Draw(g_texNum,
		Player_PositionX - PLAYER_WIDTH_HALF,
		Player_PositionY - PLAYER_HEIGHT_HALF,
		PLAYER_WIDTH, PLAYER_HEIGHT,
		PLAYER_TEXTURE_CUT_X,
		PLAYER_TEXTURE_CUT_Y,
		PLAYER_WIDTH, PLAYER_HEIGHT);
}
