#include "RightUpMove.h"
void RightUpMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	*angle = DegToRad(135);
	pos->x += cos(*angle) * moveSpeed * elapsedTime;
	pos->y -= sin(*angle) * moveSpeed * elapsedTime;
}
