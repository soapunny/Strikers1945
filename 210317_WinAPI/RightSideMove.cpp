#include "RightSideMove.h"

void RightSideMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	if (pos->x < 400) //이거 살리면 멈춤
	{
		//*angle = DegToRad(90); //그니까 오른쪽이 시작점이었지?
		pos->x +=  moveSpeed * elapsedTime * 5;//cos(*angle) *
		//pos->y -= sin(*angle) * moveSpeed * elapsedTime * 10;
	}
}
