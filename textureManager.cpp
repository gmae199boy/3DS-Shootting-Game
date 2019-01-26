#include "texture.h"
#include <string.h>


#define TEXTURE_FILENAME_MAX (64)
#define TEXTURE_MANAGE_MAX   (32)


typedef struct TextureManage_tag
{
	char filename[TEXTURE_FILENAME_MAX];
	unsigned int texture;
	int w, h; // テクスチャの幅,高さ
}TextureManage;


TextureManage g_Textures[TEXTURE_MANAGE_MAX];


// テクスチャマネージャーの初期化
void TextureManager_Initialize(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {
		g_Textures[i].filename[0] = 0;
		g_Textures[i].texture = 0xffffffff;
	}
}

// ロードするファイルの登録
//
// 引数:pFileName ... ファイル名
//      w         ... テクスチャの幅
//      h         ... テクスチャの高さ
//
// 戻り値:テクスチャ管理番号
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

		// ファイル名のコピー
		strcpy(g_Textures[i].filename, pFileName);
		// テクスチャの幅、高さの登録
		g_Textures[i].w = w;
		g_Textures[i].h = h;

		// 登録完了
		return i; // <--- これが管理番号
	}

	return -1; // もう管理できましぇ～ん
}

// テクスチャの読み込み
void TextureManager_Load(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {

		if (g_Textures[i].filename[0] == 0) {
			continue;
		}

		// <--- ファイル名が登録されている --->

		// ファイルがすでにロードされているか？
		if (g_Textures[i].texture != 0xffffffff) {
			continue;
		}

		// <--- ファイルをロードする --->
		g_Textures[i].texture = LoadTexture(g_Textures[i].filename);
	}
}

// 指定したテクスチャの解放
//
// 引数:解放したいテクスチャの管理番号
//
void TextureManager_Release(int index)
{
	if (g_Textures[index].texture != 0xffffffff) {
		g_Textures[index].filename[0] = 0;
		UnloadTexture(g_Textures[index].texture);
		g_Textures[index].texture = 0xffffffff;
	}
}

// すべてのテクスチャの解放
void TextureManager_Release(void)
{
	for (int i = 0; i < TEXTURE_MANAGE_MAX; i++) {
		TextureManager_Release(i);
	}
}

// テクスチャの取得
//
// 引数:取得したいテクスチャの管理番号
//
unsigned int TextureManager_GetTexture(int index)
{
	return g_Textures[index].texture;
}

// テクスチャの幅取得
//
// 引数:取得したいテクスチャの管理番号
//
int TextureManager_GetTextureWidth(int index)
{
	return g_Textures[index].w;
}

// テクスチャの高さ取得
//
// 引数:取得したいテクスチャの管理番号
//
int TextureManager_GetTextureHeight(int index)
{
	return g_Textures[index].h;
}

