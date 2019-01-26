#ifndef COLLISION_H_
#define COLLISION_H_

// 円をあらわす構造体
typedef struct Circle_tag
{
	float cx; // 中心座標x
	float cy; // 中心座標y
	float radius; // 半径
}Circle;

// 円Aと円Bとの当たり判定
//
// 引数:pA ... 円Aのアドレス
//      pB ... 円Bのアドレス
// 
// 戻り値:当たってたらtrueを返す
//
bool Collision_IsHitCircle(
	const Circle* pA,
	const Circle* pB
);

#endif // COLLISION_H_