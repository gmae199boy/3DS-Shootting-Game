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

// シーンの切り替え関数
//
// 引数:次のシーン番号
//
void Scene_ChangeScene(int nextScene);

// シーンの切り替え確認関数
//
void Scene_Check(void);

#endif // SCENE_H_
