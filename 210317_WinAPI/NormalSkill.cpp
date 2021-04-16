#include "NormalSkill.h"

void NormalSkill::UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime)
{
	//������ �Ʒ��� ���ϴ� �̻��� �߻�
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;
}
