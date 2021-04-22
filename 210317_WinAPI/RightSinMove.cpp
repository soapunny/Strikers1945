#include "RightSinMove.h"

void RightSinMove::DoMove(FPOINT* pos, float* angle)
{
	if (*angle < 0.0f)
	{
		*angle += 2 * PI;
	}
	else if (*angle > 2 * PI)
	{
		*angle -= 2 * PI;
	}

	if (pos->x > WINSIZE_X/ 5) {
		float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
		float angleChange = 1.2f;

		if (pos->y < 0)
		{
			*angle = DegToRad(270);
		}
		else if (*angle >= DegToRad(0) && *angle < DegToRad(90)) {//TODO 제대로 값 들어가게 바꿔주기
			dir = 1;
		}
		else if (*angle < DegToRad(360) && *angle > DegToRad(270)) {
			dir = -1;
		}
		*angle += dir * elapsedTime * angleChange;

		pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
}

void RightSinMove::Renew()
{
	time = 0.0f;
}
