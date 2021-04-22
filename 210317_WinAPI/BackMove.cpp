#include "BackMove.h"

void BackMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	*angle = DegToRad(90);
	pos->x += cos(*angle) * moveSpeed * elapsedTime;
	pos->y -= sin(*angle) * moveSpeed * elapsedTime;

}

void BackMove::Renew()
{
	time = 0.0f;
}
