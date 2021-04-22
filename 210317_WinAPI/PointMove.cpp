#include "PointMove.h"

void PointMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	//if (index <= 5)
	{
		float y = pos->y - point[0][1];		//index
		float x = -pos->x + point[0][0];

		pos->x += cosf(atan2(y, x)) * moveSpeed * 40 * elapsedTime;
		pos->y -= sinf(atan2(y, x)) * moveSpeed * 40 * elapsedTime;

		//if ((pos->y == point[index][1] && pos->x == point[index][0]))
			//index++;
	}
}

