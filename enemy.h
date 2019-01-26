#ifndef ENEMY_H_
#define ENEMY_H_

#include "collision.h"


void Enemy_Initialize(void);
void Enemy_Update(void);
void Enemy_Draw(void);

// �G�����
//
// ���� : x ... �o�����Wx
//        y ... �o�����Wy
//
void Enemy_Create(float x, float y);

// �G�̓����蔻����擾����
const Circle* Enemy_GetCollision(void);

// �G�𖳌��ɂ���
void Enemy_Destroy(void);

// �G�̑��݂��`�F�b�N����
//
// �߂�l:���݂��Ă�����true
//
bool Enemy_IsEnable(void);

#endif // ENEMY_H_
