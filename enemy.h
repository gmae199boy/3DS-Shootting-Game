#ifndef ENEMY_H_
#define ENEMY_H_

#include "collision.h"


void Enemy_Initialize(void);
void Enemy_Update(void);
void Enemy_Draw(void);

// 敵を作る
//
// 引数 : x ... 出現座標x
//        y ... 出現座標y
//
void Enemy_Create(float x, float y);

// 敵の当たり判定を取得する
const Circle* Enemy_GetCollision(void);

// 敵を無効にする
void Enemy_Destroy(void);

// 敵の存在をチェックする
//
// 戻り値:存在していたらtrue
//
bool Enemy_IsEnable(void);

#endif // ENEMY_H_
