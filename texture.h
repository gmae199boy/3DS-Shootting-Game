#ifndef TEXTURE_H_
#define TEXTURE_H_

// テクスチャの読み込み
//
// 引数 : pFileName ... ファイル名
//
// 戻り値 : テクスチャ番号
unsigned int LoadTexture(const char *pFileName);

// 読み込んだテクスチャの破棄
//
// 引数 : Texture ... テクスチャ番号
//
void UnloadTexture(unsigned int Texture);

#endif // TEXTURE_H_
