#ifndef PLAYER_H_
#define PLAYER_H_

#include <nn/math.h>

// �v���C���[�̏�����
void Player_Initialize(void);

// �v���C���[�̈ړ�
void Player_MoveFront(void);
void Player_MoveRight(void);
void Player_MoveLeft(void);
void Player_MoveBack(void);

// �e�̔���
void Player_Shot(void);

// void Player_Move(const nn::math::VEC2* pV);

// �v���C���[�̍X�V
void Player_Update(void);

// �v���C���[�̕`��
void Player_Draw(void);

#endif // PLAYER_H_
