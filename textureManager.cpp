#include "texture.h"
#include <string.h>


#define TEXTURE_FILENAME_MAX (64)
#define TEXTURE_MANAGE_MAX   (32)


typedef struct TextureManage_tag
{
	char filename[TEXTURE_FILENAME_MAX];
	unsigned int texture;
	int w, h; // �e�N�X�`���̕�,����
}TextureManage;


TextureManage g_Textures[TEXTURE_MANAGE_MAX];


// �e�N�X�`���}�l�[�W���[�̏�����
void TextureManager_Initialize(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {
		g_Textures[i].filename[0] = 0;
		g_Textures[i].texture = 0xffffffff;
	}
}

// ���[�h����t�@�C���̓o�^
//
// ����:pFileName ... �t�@�C����
//      w         ... �e�N�X�`���̕�
//      h         ... �e�N�X�`���̍���
//
// �߂�l:�e�N�X�`���Ǘ��ԍ�
//
int TextureManager_SetFile(const char* pFileName, int w, int h)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {

		if (g_Textures[i].filename[0] == 0) {
			continue;
		}

		if (strcmp(g_Textures[i].filename, pFileName) == 0) {
			return i;
		}
	}

	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {

		if (g_Textures[i].filename[0] != 0) {
			continue;
		}

		// �t�@�C�����̃R�s�[
		strcpy(g_Textures[i].filename, pFileName);
		// �e�N�X�`���̕��A�����̓o�^
		g_Textures[i].w = w;
		g_Textures[i].h = h;

		// �o�^����
		return i; // <--- ���ꂪ�Ǘ��ԍ�
	}

	return -1; // �����Ǘ��ł��܂����`��
}

// �e�N�X�`���̓ǂݍ���
void TextureManager_Load(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {

		if (g_Textures[i].filename[0] == 0) {
			continue;
		}

		// <--- �t�@�C�������o�^����Ă��� --->

		// �t�@�C�������łɃ��[�h����Ă��邩�H
		if (g_Textures[i].texture != 0xffffffff) {
			continue;
		}

		// <--- �t�@�C�������[�h���� --->
		g_Textures[i].texture = LoadTexture(g_Textures[i].filename);
	}
}

// �w�肵���e�N�X�`���̉��
//
// ����:����������e�N�X�`���̊Ǘ��ԍ�
//
void TextureManager_Release(int index)
{
	if (g_Textures[index].texture != 0xffffffff) {
		g_Textures[index].filename[0] = 0;
		UnloadTexture(g_Textures[index].texture);
		g_Textures[index].texture = 0xffffffff;
	}
}

// ���ׂẴe�N�X�`���̉��
void TextureManager_Release(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {
		TextureManager_Release(i);
	}
}

// �e�N�X�`���̎擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
unsigned int TextureManager_GetTexture(int index)
{
	return g_Textures[index].texture;
}

// �e�N�X�`���̕��擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
int TextureManager_GetTextureWidth(int index)
{
	return g_Textures[index].w;
}

// �e�N�X�`���̍����擾
//
// ����:�擾�������e�N�X�`���̊Ǘ��ԍ�
//
int TextureManager_GetTextureHeight(int index)
{
	return g_Textures[index].h;
}

