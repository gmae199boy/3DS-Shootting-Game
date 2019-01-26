#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

// ’e‚ÌÅ‘å”iŠÇ—”j
#define BULLET_COUNT_MAX (128)


void Bullet_Initialize(void);
void Bullet_Update(void);
void Bullet_Draw(void);

// ’e‚ğì‚é
//
// ˆø” : x ... ”­ËÀ•Wx
//        y ... ”­ËÀ•Wy
//
void Bullet_Create(float x, float y);

// ’e‚Ì“–‚½‚è”»’è‚ğæ“¾‚·‚é
const Circle* Bullet_GetCollision(int index);

// ’e‚ğ–³Œø‚É‚·‚é
void Bullet_Destroy(int index);

// ’e‚ª—LŒø‚©æ“¾‚·‚é
bool Bullet_IsEnable(int index);

#endif // BULLET_H_
