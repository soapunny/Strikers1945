#include "ZigzagMove.h"

void ZigzagMove::DoMove(FPOINT* pos, float* angle)
{
	
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
		(*angle) += 180 * elapsedTime * 2;//������ �����ӿ����� �޳�
		
		//�Ѱ�ü�� �����ӿ� ���� �� �����غ����ҵ�
		
		pos->x += cos(DegToRad((*angle))) * moveSpeed * elapsedTime * 150;//cos(*angle) *
		pos->y -= sin(DegToRad((*angle))) * moveSpeed * elapsedTime * 150;
		
	
}
