#include "RightSinMove.h"

void RightSinMove::DoMove(FPOINT* pos, float* angle)
{
	if (pos->x > WINSIZE_X/ 5) {
		/*float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
		int tmpX = pos->x;
		float angleChange = 2.0f;
		tmpX = tmpX / 80;

		if (tmpX % 4 < 1) {
			*angle -= elapsedTime * angleChange;
		}
		else if (tmpX % 4 < 2) {
			*angle += elapsedTime * angleChange;
		}
		else if (tmpX % 4 < 3) {
			*angle -= elapsedTime * angleChange;
		}
		else
			*angle += elapsedTime * angleChange;


		pos->x -= cosf(*angle) * elapsedTime * moveSpeed;
		pos->y -= sinf(*angle) * elapsedTime * moveSpeed;*/

		//float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
		//int tmpX = pos->x;
		//float angleChange = 1.2f;
		//tmpX = (WINSIZE_X - tmpX) / 80;

		//if (tmpX % 4 < 1) {
		//	*angle -= elapsedTime * angleChange;
		//}
		//else if (tmpX % 4 < 3) {
		//	*angle += elapsedTime * angleChange;
		//}
		//else
		//	*angle -= elapsedTime * angleChange;


		//pos->x -= cosf(*angle) * elapsedTime * moveSpeed;
		//pos->y -= sinf(*angle) * elapsedTime * moveSpeed;


		if (pos->x > WINSIZE_X * 1 / 5) {
			float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
			float angleChange = 1.2f;

			if (pos->y < WINSIZE_Y / 3) {
				*angle -= elapsedTime * angleChange;
			}
			else if (pos->y < WINSIZE_Y) {
				*angle += elapsedTime * angleChange;
			}

			pos->x -= /*cosf(*angle) * */elapsedTime * moveSpeed;
			pos->y -= sinf(*angle) * elapsedTime * moveSpeed;
		}
	}
}

void RightSinMove::Renew()
{
	time = 0.0f;
}
