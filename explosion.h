#ifndef EXPLOSION_H_
#define EXPLOSION_H_

void Explosion_Initialize(void);
void Explosion_Update(void);
void Explosion_Draw(void);

// 爆発エフェクトの再生
//
// 引数 : x ... 再生座標x
//        y ... 再生座標y
//
void Explosion_Create(float x, float y);

#endif // EXPLOSION_H_