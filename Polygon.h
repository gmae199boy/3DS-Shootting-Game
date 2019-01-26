#ifndef POLYGON_H_
#define POLYGON_H_


// �|���S���`��̏�����
void Polygon_Initialize(void);

// �|���S���`��̏I������
void Polygon_Finalize(void);

// �|���S���`��
//
// ���� : texNum ... �e�N�X�`���Ǘ��ԍ�
//      : dx     ... �`����Wx
//      : dy     ... �`����Wy
//      : dw     ... ��
//      : dh     ... ����
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh);

// �|���S���`��
//
// ���� : texNum ... �e�N�X�`���Ǘ��ԍ�
//      : dx     ... �`����Wx
//      : dy     ... �`����Wy
//      : dw     ... ��
//      : dh     ... ����
//      : tcx    ... �e�N�X�`���̐؂�����Wx
//      : tcy    ... �e�N�X�`���̐؂�����Wy
//      : tcw    ... �e�N�X�`���̐؂��蕝
//      : tch    ... �e�N�X�`���̐؂��荂��
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh,
	int tcx, int tcy, int tcw, int tch);

// �|���S���`��
//
// ���� : texNum ... �e�N�X�`���Ǘ��ԍ�
//      : dx     ... �`����Wx
//      : dy     ... �`����Wy
//      : dw     ... ��
//      : dh     ... ����
//      : cx     ... ���S���Wx
//      : cy     ... ���S���Wy
//      : sx     ... �g�嗦x
//      : sy     ... �g�嗦y
//      : ang    ... ��]�p�x(���W�A��)
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh, float cx, float cy, float sx, float sy, float ang);

#endif // POLYGON_H_

