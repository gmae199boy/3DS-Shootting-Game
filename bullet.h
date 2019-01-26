#ifndef BULLET_H_
#define BULLET_H_

#include "collision.h"

// �e�̍ő吔�i�Ǘ����j
#define BULLET_COUNT_MAX (128)


void Bullet_Initialize(void);
void Bullet_Update(void);
void Bullet_Draw(void);

// �e�����
//
// ���� : x ... ���ˍ��Wx
//        y ... ���ˍ��Wy
//
void Bullet_Create(float x, float y);

// �e�̓����蔻����擾����
const Circle* Bullet_GetCollision(int index);

// �e�𖳌��ɂ���
void Bullet_Destroy(int index);

// �e���L�����擾����
bool Bullet_IsEnable(int index);

#endif // BULLET_H_
