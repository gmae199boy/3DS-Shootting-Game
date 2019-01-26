#ifndef POLYGON_H_
#define POLYGON_H_


// ポリゴン描画の初期化
void Polygon_Initialize(void);

// ポリゴン描画の終了処理
void Polygon_Finalize(void);

// ポリゴン描画
//
// 引数 : texNum ... テクスチャ管理番号
//      : dx     ... 描画座標x
//      : dy     ... 描画座標y
//      : dw     ... 幅
//      : dh     ... 高さ
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh);

// ポリゴン描画
//
// 引数 : texNum ... テクスチャ管理番号
//      : dx     ... 描画座標x
//      : dy     ... 描画座標y
//      : dw     ... 幅
//      : dh     ... 高さ
//      : tcx    ... テクスチャの切り取り座標x
//      : tcy    ... テクスチャの切り取り座標y
//      : tcw    ... テクスチャの切り取り幅
//      : tch    ... テクスチャの切り取り高さ
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh,
	int tcx, int tcy, int tcw, int tch);

// ポリゴン描画
//
// 引数 : texNum ... テクスチャ管理番号
//      : dx     ... 描画座標x
//      : dy     ... 描画座標y
//      : dw     ... 幅
//      : dh     ... 高さ
//      : cx     ... 中心座標x
//      : cy     ... 中心座標y
//      : sx     ... 拡大率x
//      : sy     ... 拡大率y
//      : ang    ... 回転角度(ラジアン)
void Polygon_Draw(
	int texNum,
	float dx, float dy, float dw, float dh, float cx, float cy, float sx, float sy, float ang);

#endif // POLYGON_H_

