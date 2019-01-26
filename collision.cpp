#include "collision.h"

bool Collision_IsHitCircle(const Circle* pA, const Circle* pB)
{
	float xl = pB->cx - pA->cx;
	float yl = pB->cy - pA->cy;
	float rl = pA->radius + pB->radius;

	return rl * rl > xl * xl + yl * yl;
}
