#include "RightSideMove.h"

void RightSideMove::DoMove(FPOINT* pos, float* angle)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	if (pos->x < 400) //�̰� �츮�� ����
	{
		//*angle = DegToRad(90); //�״ϱ� �������� �������̾���?
		pos->x +=  moveSpeed * elapsedTime * 5;//cos(*angle) *
		//pos->y -= sin(*angle) * moveSpeed * elapsedTime * 10;
	}
}
