
#include "LeftDownMove.h"

void LeftDownMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//if (pos->x < -400)
	{
		*angle = DegToRad(45);
		pos->x += cos(*angle) * moveSpeed * elapsedTime*10;
		pos->y -= sin(*angle) * moveSpeed * elapsedTime*10;
	}
}

void LeftDownMove::Renew()
{
	time = 0.0f;
}
