#ifndef PLAYER_H_
#define PLAYER_H_

#include <nn/math.h>

// プレイヤーの初期化
void Player_Initialize(void);

// プレイヤーの移動
void Player_MoveFront(void);
void Player_MoveRight(void);
void Player_MoveLeft(void);
void Player_MoveBack(void);

// 弾の発射
void Player_Shot(void);

// void Player_Move(const nn::math::VEC2* pV);

// プレイヤーの更新
void Player_Update(void);

// プレイヤーの描画
void Player_Draw(void);

#endif // PLAYER_H_
