#ifndef EXPLOSION_H_
#define EXPLOSION_H_

void Explosion_Initialize(void);
void Explosion_Update(void);
void Explosion_Draw(void);

// �����G�t�F�N�g�̍Đ�
//
// ���� : x ... �Đ����Wx
//        y ... �Đ����Wy
//
void Explosion_Create(float x, float y);

#endif // EXPLOSION_H_