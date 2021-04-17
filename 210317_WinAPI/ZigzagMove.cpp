#include "ZigzagMove.h"

void ZigzagMove::DoMove(FPOINT* pos, float* angle)
{
	
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
		(*angle) += 180 * elapsedTime * 2;//각도도 프레임영향을 받네
		
		//한객체의 움직임에 대해 더 연구해봐야할듯
		
		pos->x += cos(DegToRad((*angle))) * moveSpeed * elapsedTime * 150;//cos(*angle) *
		pos->y -= sin(DegToRad((*angle))) * moveSpeed * elapsedTime * 150;
		
	
}
