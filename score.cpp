#include "number.h"


void Score_Draw(int score, int fig, float x, float y)
{
	// カンストチェック
	// fig = 7 ...  10000000
	int cs = 1;
	for (int i = 0; i < fig; i++) {
		cs *= 10; // cs = cs * 10;
	}
	cs -= 1; // 9999999

	if (score > cs) {
		score = cs;
	}

	for (int i = 0; i < fig; i++) {
		int n = score % 10;
		Number_Draw(n, 
			x + NUMBER_CUT_WIDTH 
			* (fig - 1 - i), y);
		score /= 10;
	}
}
