#include "LeftUpMove.h"

void LeftUpMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	*angle = DegToRad(45);
	pos->x += cos(*angle) * moveSpeed * elapsedTime;
	pos->y -= sin(*angle) * moveSpeed * elapsedTime;

}
