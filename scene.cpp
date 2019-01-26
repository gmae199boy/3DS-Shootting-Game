#include <nn/hid.h>
#include "scene.h"
#include "title.h"
#include "game.h"
#include "hiscore.h"


static int g_NowScene = SCENE_TITLE;
static int g_NextScene = g_NowScene;

typedef void(*SceneFunc)(void);
typedef void(*SceneFuncUpdate)(nn::hid::PadStatus* pPadStatus);


static const SceneFunc INITIALIZE[] = {
	Title_Initialize,
	Game_Initialize,
	Hiscore_Initialize
};

static const SceneFunc FINALAIZE[] = {
	Title_Finalize,
	Game_Finalize,
	Hiscore_Finalize
};

static const SceneFuncUpdate UPDATE[] = {
	Title_Update,
	Game_Update,
	Hiscore_Update
};

static const SceneFunc DRAW[] = {
	Title_Draw,
	Game_Draw,
	Hiscore_Draw
};

void Scene_Initialize(void)
{
	INITIALIZE[g_NowScene]();
}

void Scene_Finalize(void)
{
	FINALAIZE[g_NowScene]();
}

void Scene_Update(nn::hid::PadStatus* pPadStatus)
{
	UPDATE[g_NowScene](pPadStatus);
}

void Scene_Draw(void)
{
	DRAW[g_NowScene]();
}

// �V�[���̐؂�ւ��֐�
//
// ����:���̃V�[���ԍ�
//
void Scene_ChangeScene(int nextScene)
{
	g_NextScene = nextScene;
}


// �V�[���̐؂�ւ��m�F�֐�
//
void Scene_Check(void)
{
	// ���̃V�[���Ǝ��̃V�[����
	// �Ⴄ�ԍ���������؂�ւ���
	if (g_NowScene != g_NextScene) {

		// ���̃V�[���̏I������
		Scene_Finalize();

		g_NowScene = g_NextScene;

		// ���̃V�[��
		// (�V�������ɂȂ����V�[���j
		// �̏�����
		Scene_Initialize();
	}
}
