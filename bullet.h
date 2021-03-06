#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

// 弾の最大数（管理数）
#define BULLET_COUNT_MAX (128)


void Bullet_Initialize(void);
void Bullet_Update(void);
void Bullet_Draw(void);

// 弾を作る
//
// 引数 : x ... 発射座標x
//        y ... 発射座標y
//
void Bullet_Create(float x, float y);

// 弾の当たり判定を取得する
const Circle* Bullet_GetCollision(int index);

// 弾を無効にする
void Bullet_Destroy(int index);

// 弾が有効か取得する
bool Bullet_IsEnable(int index);

#endif // BULLET_H_
