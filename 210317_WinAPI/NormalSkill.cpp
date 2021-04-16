#include "NormalSkill.h"

void NormalSkill::UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime)
{
	//일직선 아래로 향하는 미사일 발사
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;
}
