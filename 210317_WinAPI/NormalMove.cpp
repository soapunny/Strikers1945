#include "NormalMove.h"

void NormalMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	if (pos->y < 400)
	{
		pos->y += elapsedTime * 100 * moveSpeed;
	}
}

void NormalMove::Renew()
{
	time = 0.0f;
}
 