#ifndef NUMBER_H_
#define NUMBER_H_

#define NUMBER_CUT_WIDTH  (16)
#define NUMBER_CUT_HEIGHT (16)


void Number_Initialize(void);

// ���l�̕\���֐�
//
// ����:n ... �ꌅ�̐��l(0�`9)
//      x ... �\�����Wx
//      y ... �\�����Wy
void Number_Draw(int n, float x, float y);

#endif // NUMBER_H_