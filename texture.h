#ifndef TEXTURE_H_
#define TEXTURE_H_

// �e�N�X�`���̓ǂݍ���
//
// ���� : pFileName ... �t�@�C����
//
// �߂�l : �e�N�X�`���ԍ�
unsigned int LoadTexture(const char *pFileName);

// �ǂݍ��񂾃e�N�X�`���̔j��
//
// ���� : Texture ... �e�N�X�`���ԍ�
//
void UnloadTexture(unsigned int Texture);

#endif // TEXTURE_H_
