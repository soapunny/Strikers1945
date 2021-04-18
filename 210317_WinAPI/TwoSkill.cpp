#include "TwoSkill.h"
void TwoSkill::UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime)
{
	//������ �Ʒ��� ���ϴ� �̻��� �߻�
	//srand(time(NULL));
	//moveSpeed = rand() % 50*10;	

	currTime++;

	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;

	if (currTime > 1)
	{
		moveSpeed = 0;
	}
}