#include <nn/hid.h>
#include "scene.h"
#include "Polygon.h"
#include "textureManager.h"


static int g_texNum = -1;


void Hiscore_Initialize(void)
{
	g_texNum = TextureManager_SetFile("rom:/hiscore.tga", 512, 512);
	TextureManager_Load();
}

void Hiscore_Finalize(void)
{
	TextureManager_Release();
}

void Hiscore_Update(nn::hid::PadStatus* pPadStatus)
{
	if (pPadStatus->trigger & nn::hid::BUTTON_A) {
		Scene_ChangeScene(SCENE_TITLE);
	}
}

void Hiscore_Draw(void)
{
	Polygon_Draw(g_texNum, 0.0f, 0.0f, 400, 240, 0, 0, 400, 240);
}
