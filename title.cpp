#include <nn/hid.h>
#include "scene.h"
#include "textureManager.h" // ①
#include "Polygon.h"


static int g_TexNum = -1; // ②


void Title_Initialize(void)
{
	// ③
	g_TexNum = TextureManager_SetFile("rom:/title.tga", 512, 512);
	TextureManager_Load(); // ④ 
}

void Title_Finalize(void)
{
	TextureManager_Release();
}

void Title_Update(nn::hid::PadStatus* pPadStatus)
{
	if (pPadStatus->trigger & nn::hid::BUTTON_A) {
		Scene_ChangeScene(SCENE_GAME);
	}
}

void Title_Draw(void)
{
	//              ⑤　　　　　　　　　　　　　　　　　　　　　　⑥
	Polygon_Draw(g_TexNum, 0.0f, 0.0f, 400, 240, 0, 0, 400, 240);
}
