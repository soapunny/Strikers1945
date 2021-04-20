#include "SpearMove.h"

void SpearMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	time += elapsedTime;

	if (time < 10){
		*angle = atan2((pos->y - limitRect.top), (limitRect.left - pos->x));
		if (pos->x > limitRect.left)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		if (pos->y > limitRect.top)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
	else if (time < 11) {
		*angle *= dir;
		dir *= -1;
		//pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
		if (lpPlayerPos != nullptr) {
			*angle = atan2(pos->y - lpPlayerPos->y, lpPlayerPos->x - pos->x);
			if (*angle < atan2(pos->y - limitRect.bottom, limitRect.left - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.left - pos->x);
			else if(*angle > atan2(pos->y - limitRect.bottom, limitRect.right - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.right - pos->x);
		}
		else
			*angle = atan2((pos->y - limitRect.bottom), (WINSIZE_X / 2.0 - pos->x));
	}
	else if (time < 15)
	{
		if (pos->y < limitRect.bottom){
			pos->x += cosf(*angle) * elapsedTime * moveSpeed*20;
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed*20;
		}
	}
	else if (time < 24) {
		*angle = atan2((pos->y - limitRect.top), (WINSIZE_X / 2.0 - pos->x));
		
		if (pos->y > limitRect.top) {
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		}
	}
	else if (time < 25) {
		*angle *= dir;
		dir *= -1;
		//pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
		if (lpPlayerPos != nullptr) {
			*angle = atan2(pos->y - lpPlayerPos->y, lpPlayerPos->x - pos->x);
			if (*angle < atan2(pos->y - limitRect.bottom, limitRect.left - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.left - pos->x);
			else if (*angle > atan2(pos->y - limitRect.bottom, limitRect.right - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.right - pos->x);
		}
		else
			*angle = atan2((pos->y - limitRect.bottom), (WINSIZE_X / 2.0 - pos->x));
	}
	else if (time < 30)
	{
		if (pos->y < limitRect.bottom) {
			pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
		}
	}
	else if (time < 40) {
		/*if (pos->x < WINSIZE_X*4 / 5)
			pos->x += elapsedTime * moveSpeed;
		if (pos->y > WINSIZE_Y / 5)
			pos->y -= elapsedTime * moveSpeed;*/
		*angle = atan2((pos->y - limitRect.top), (limitRect.right - pos->x));
		if (pos->x < limitRect.right)
			pos->x += cosf(*angle) * elapsedTime * moveSpeed;
		if (pos->y > limitRect.top)
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
	}
	else if (time < 41) {
		*angle *= dir;
		dir *= -1;
		//pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
		if (lpPlayerPos != nullptr) {
			*angle = atan2(pos->y - lpPlayerPos->y, lpPlayerPos->x - pos->x);
			if (*angle < atan2(pos->y - limitRect.bottom, limitRect.left - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.left - pos->x);
			else if (*angle > atan2(pos->y - limitRect.bottom, limitRect.right - pos->x))
				*angle = atan2(pos->y - limitRect.bottom, limitRect.right - pos->x);
		}
		else
			*angle = atan2((pos->y - limitRect.bottom), (WINSIZE_X / 2.0 - pos->x));
	}
	else if (time < 45)
	{
		if (pos->y < limitRect.bottom) {
			pos->x += cosf(*angle) * elapsedTime * moveSpeed * 20;
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed * 20;
		}
	}
	else {
		time = 0.0f;
	}
}


void SpearMove::Renew() {
	time = 0.0f;
	dir = 1;
}
