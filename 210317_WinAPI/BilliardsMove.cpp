#include "BilliardsMove.h"
#include <ctime>

void BilliardsMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	time += elapsedTime;


	if(time < 20.0f){
		if (*angle >= 2 * PI) {
			*angle -= 2 * PI;
		}
		else if (*angle < 0)
		{
			*angle += 2 * PI;
		}

		if (pos->x <= bossSize / 2)
		{
			if (*angle == PI)
				*angle = 0.0f;
			else
			{
				*angle = (PI - *angle);
			}

		}
		else if (pos->x >= WINSIZE_X - bossSize / 2)
		{
			if (*angle == 0)
				*angle = PI;
			else
			{
				*angle = (PI - *angle);
			}
		}
		else if (pos->y <= bossSize / 2)
		{
			if (*angle == PI/2)
				*angle = PI*3/2;
			else
			{
				*angle = -(*angle);
			}
		}
		else if (pos->y >= WINSIZE_Y - bossSize / 2)
		{
			if (*angle == PI * 3 / 2)
				*angle = PI / 2;
			else
			{
				*angle = -(*angle);
			}
		}

		pos->x += cos(*angle) * moveSpeed * elapsedTime;
		pos->y -= sin(*angle) * moveSpeed * elapsedTime;
	}
	else if (time < 25.0f)
	{

	}
	else {
		Renew();
		srand(std::time(NULL));
		*angle = rand() % 314 / 100.0f;
	}

}