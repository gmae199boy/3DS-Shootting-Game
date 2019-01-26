#ifndef NUMBER_H_
#define NUMBER_H_

#define NUMBER_CUT_WIDTH  (16)
#define NUMBER_CUT_HEIGHT (16)


void Number_Initialize(void);

// 数値の表示関数
//
// 引数:n ... 一桁の数値(0～9)
//      x ... 表示座標x
//      y ... 表示座標y
void Number_Draw(int n, float x, float y);

#endif // NUMBER_H_