#include <nn/hid.h>
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "explosion.h"
#include "main.h"
#include "number.h"
#include "score.h"
#include "scene.h"
#include "textureManager.h"


static int g_Game_Score = 0;


void Game_Initialize(void)
{
	Player_Initialize();
	Bullet_Initialize();
	Enemy_Initialize();
	Explosion_Initialize();
	Number_Initialize();

	TextureManager_Load();

	g_Game_Score = 0;
}

void Game_Finalize(void)
{
	TextureManager_Release();
}

void Game_Update(nn::hid::PadStatus* pPadStatus)
{
	if (pPadStatus->hold & nn::hid::BUTTON_RIGHT) {
		// 右キーが押された
		Player_MoveRight();
	}
	if (pPadStatus->hold & nn::hid::BUTTON_LEFT) {
		// 右キーが押された
		Player_MoveLeft();
	}
	if (pPadStatus->hold & nn::hid::BUTTON_UP) {
		// 右キーが押された
		Player_MoveFront();
	}
	if (pPadStatus->hold & nn::hid::BUTTON_DOWN) {
		// 右キーが押された
		Player_MoveBack();
	}

	Player_Update();
	
	if (pPadStatus->trigger & nn::hid::BUTTON_A) {
		Player_Shot();
	}

	Bullet_Update();
	Enemy_Update();

	if (!Enemy_IsEnable()) {

		Enemy_Create(SCREEN_0_WIDTH + 32, 32.0f);
	}

	for (int i = 0; i < BULLET_COUNT_MAX; i++) {
		
		if (Enemy_IsEnable() && Bullet_IsEnable(i)) {

			if (Collision_IsHitCircle(
				Enemy_GetCollision(),
				Bullet_GetCollision(i))) {

				Explosion_Create(
					Enemy_GetCollision()->cx,
					Enemy_GetCollision()->cy);

				g_Game_Score += 100;

				Enemy_Destroy();
				Bullet_Destroy(i);
			}
		}
	}

	Explosion_Update();

	// 画面遷移テスト
	if (g_Game_Score >= 300) {
		Scene_ChangeScene(SCENE_HISCORE);
	}
}

void Game_Draw(void)
{
	Player_Draw();
	Bullet_Draw();
	Enemy_Draw();
	Explosion_Draw();

	Score_Draw(g_Game_Score, 3, 0, 0);
}
