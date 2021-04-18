#include "LeftSinMove.h"

void LeftSinMove::DoMove(FPOINT* pos, float* angle)
{
	if(pos->x < WINSIZE_X*4/5){
		float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
		float angleChange = 1.2f;

		if (pos->y < WINSIZE_Y/3) {
			*angle -= elapsedTime * angleChange;
		}
		else if (pos->y < WINSIZE_Y) {
			*angle += elapsedTime * angleChange;
		}

		pos->x += /*cosf(*angle) * */elapsedTime * moveSpeed;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
}

void LeftSinMove::Renew()
{
	time = 0.0f;
}
