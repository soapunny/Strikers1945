#include "RightMove.h"
void RightMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//if (pos->y < 400)
	{
		pos->x += moveSpeed * elapsedTime;;
	}
}
