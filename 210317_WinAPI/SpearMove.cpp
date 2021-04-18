#include "SpearMove.h"

void SpearMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	time += elapsedTime;

	if (time < 10) {
		/*if(pos->x > WINSIZE_X/5)
			pos->x -= elapsedTime * moveSpeed;
		if(pos->y > WINSIZE_Y/5)
			pos->y -= elapsedTime * moveSpeed;*/
		*angle = atan2((pos->y - WINSIZE_Y / 5.0), (WINSIZE_X / 5.0 - pos->x));
		if (pos->x > WINSIZE_X / 5.0f)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
	else if (time < 11) {
		*angle += PI;
			pos->x += cosf(*angle) * elapsedTime * moveSpeed*20;
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed*20;
	}
	else if (time < 15)
	{
		*angle = atan2((pos->y - WINSIZE_Y * 4 / 5.0), (WINSIZE_X / 2.0 - pos->x));
		if (pos->x < WINSIZE_X / 2)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed*20;
		if (pos->y < WINSIZE_Y * 4 / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed*20;
	}
	else if (time < 25) {
		/*if (pos->x < WINSIZE_X / 2)
			pos->x += elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5)
			pos->y -= elapsedTime * moveSpeed;*/
		*angle = atan2((pos->y - WINSIZE_Y / 5.0), (WINSIZE_X / 2.0 - pos->x));
		if (pos->x > WINSIZE_X / 2)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
	else if (time < 26) {
		*angle += PI;
		pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
	}
	else if (time < 30)
	{
		*angle = atan2((pos->y - WINSIZE_Y * 4 / 5.0), (WINSIZE_X / 2.0 - pos->x));
		if (pos->x < WINSIZE_X / 2)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		if (pos->y < WINSIZE_Y * 4 / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
	}
	else if (time < 40) {
		/*if (pos->x < WINSIZE_X*4 / 5)
			pos->x += elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5)
			pos->y -= elapsedTime * moveSpeed;*/
		*angle = atan2((pos->y - WINSIZE_Y / 5.0), (WINSIZE_X*4 / 5.0 - pos->x));
		if (pos->x < WINSIZE_X*4 / 5.0f)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
	else if (time < 41) {
		*angle += PI;
		pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
	}
	else if (time < 45)
	{
		*angle = atan2((pos->y - WINSIZE_Y * 4 / 5.0), (WINSIZE_X / 2.0 - pos->x));
		if (pos->x > WINSIZE_X / 2.0f)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		if (pos->y < WINSIZE_Y * 4 / 5.0f)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
	}
	else {
		time = 0.0f;
	}
}


void SpearMove::Renew() {
	time = 0.0f;
}
