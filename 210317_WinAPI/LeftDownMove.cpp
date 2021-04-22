#include "LeftDownMove.h"

void LeftDownMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	*angle = DegToRad(-45);
	pos->x += cos(*angle) * moveSpeed * elapsedTime;
	pos->y -= sin(*angle) * moveSpeed * elapsedTime;
	
}

void LeftDownMove::Renew()
{
	time = 0.0f;
}
