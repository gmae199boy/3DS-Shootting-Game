#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

// �e�N�X�`���}�l�[�W���[�̏�����
void TextureManager_Initialize(void);

// ���[�h����t�@�C���̓o�^
//
// ����:pFileName ... �t�@�C����
//      w         ... �e�N�X�`���̕�
//      h         ... �e�N�X�`���̍���
//
// �߂�l:�e�N�X�`���Ǘ��ԍ�
//
int TextureManager_SetFile(const char* pFileName, int w, int h);

// �e�N�X�`���̓ǂݍ���
void TextureManager_Load(void);

// �w�肵���e�N�X�`���̉��
//
// ����:����������e�N�X�`���̊Ǘ��ԍ�
//
void TextureManager_Release(int index);

// ���ׂẴe�N�X�`���̉��
void TextureManager_Release(void);

// �e�N�X�`���̎擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
unsigned int TextureManager_GetTexture(int index);

// �e�N�X�`���̕��擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
int TextureManager_GetTextureWidth(int index);

// �e�N�X�`���̍����擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
int TextureManager_GetTextureHeight(int index);

#endif // TEXTURE_MANAGER_H_
