#ifndef COLLISION_H_
#define COLLISION_H_

// �~������킷�\����
typedef struct Circle_tag
{
	float cx; // ���S���Wx
	float cy; // ���S���Wy
	float radius; // ���a
}Circle;

// �~A�Ɖ~B�Ƃ̓����蔻��
//
// ����:pA ... �~A�̃A�h���X
//      pB ... �~B�̃A�h���X
// 
// �߂�l:�������Ă���true��Ԃ�
//
bool Collision_IsHitCircle(
	const Circle* pA,
	const Circle* pB
);

#endif // COLLISION_H_