#include "CenterMove.h"

void CenterMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	if (pos->x < 300)*angle = DegToRad(1);
	if (pos->x > 300)*angle = DegToRad(180);
	else *angle = DegToRad(0);
	//*angle = DegToRad(-45);
	
	if(pos->x - WINSIZE_X/2 >= -5&& pos->x - WINSIZE_X / 2 <= 5)
	{
		pos->x += cos(*angle) * 0 * elapsedTime;
		pos->y -= sin(*angle) * 0 * elapsedTime;
	}
	else {
		pos->x += cos(*angle) * moveSpeed * elapsedTime;
		pos->y -= sin(*angle) * moveSpeed * elapsedTime;
	}

}