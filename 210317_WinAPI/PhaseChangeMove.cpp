#include "PhaseChangeMove.h"

void PhaseChangeMove::DoMove(FPOINT* pos, float* angle)
{
	srand(std::time(NULL));
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	if (pos->x != WINSIZE_X / 2 && pos->y != 250)
	{
		*angle = atan2(pos->y - (WINSIZE_Y / 2), pos->x - 250);
	}
	else
	{
		*angle = 0;
		moveSpeed = 0;
	}
	//*angle = DegToRad(-45);
	pos->x += cos(*angle) * moveSpeed * elapsedTime;
	pos->y -= sin(*angle) * moveSpeed * elapsedTime;


}