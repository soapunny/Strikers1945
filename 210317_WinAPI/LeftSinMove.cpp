#include "LeftSinMove.h"

void LeftSinMove::DoMove(FPOINT* pos, float* angle)
{
	
	if (*angle < 0.0f)
	{
		*angle += 2 * PI;
	}
	else if (*angle > 2 * PI)
	{
		*angle -= 2 * PI;
	}

	if (pos->x < WINSIZE_X * 4 / 5 ) {
		float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
		float angleChange = 1.2f;
		if (pos->y < 0)
		{
			*angle = DegToRad(270);
		}
		else if (*angle > DegToRad(180) && *angle < DegToRad(270)) {//TODO ����� �� ���� �ٲ��ֱ�
			dir = 1;
		}
		else if (*angle <= DegToRad(180) && *angle > DegToRad(90)) {
			dir = -1;
		}
		
		*angle += dir * elapsedTime * angleChange;

		pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
}

void LeftSinMove::Renew()
{
	time = 0.0f;
}
