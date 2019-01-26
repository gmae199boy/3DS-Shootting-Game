#ifndef SCENE_H_
#define SCENE_H_

#include <nn/hid.h>

void Scene_Initialize(void);
void Scene_Finalize(void);
void Scene_Update(nn::hid::PadStatus* pPadStatus);
void Scene_Draw(void);

enum
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_HISCORE,
	SCENE_MAX
};

// �V�[���̐؂�ւ��֐�
//
// ����:���̃V�[���ԍ�
//
void Scene_ChangeScene(int nextScene);

// �V�[���̐؂�ւ��m�F�֐�
//
void Scene_Check(void);

#endif // SCENE_H_
