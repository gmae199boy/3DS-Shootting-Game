#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

// テクスチャマネージャーの初期化
void TextureManager_Initialize(void);

// ロードするファイルの登録
//
// 引数:pFileName ... ファイル名
//      w         ... テクスチャの幅
//      h         ... テクスチャの高さ
//
// 戻り値:テクスチャ管理番号
//
int TextureManager_SetFile(const char* pFileName, int w, int h);

// テクスチャの読み込み
void TextureManager_Load(void);

// 指定したテクスチャの解放
//
// 引数:解放したいテクスチャの管理番号
//
void TextureManager_Release(int index);

// すべてのテクスチャの解放
void TextureManager_Release(void);

// テクスチャの取得
//
// 引数:取得したいテクスチャの管理番号
//
unsigned int TextureManager_GetTexture(int index);

// テクスチャの幅取得
//
// 引数:取得したいテクスチャの管理番号
//
int TextureManager_GetTextureWidth(int index);

// テクスチャの高さ取得
//
// 引数:取得したいテクスチャの管理番号
//
int TextureManager_GetTextureHeight(int index);

#endif // TEXTURE_MANAGER_H_
