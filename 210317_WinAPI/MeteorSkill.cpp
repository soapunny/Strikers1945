#include "MeteorSkill.h"
#include "Missile.h"

void MeteorSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//������ �Ʒ��� ���ϴ� �̻��� �߻�
	//srand(time(NULL));
	//moveSpeed = rand() % 50*10;	

	currTime++;

	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();	
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();

	if (currTime > 1)
	{
		//missile->SetMoveSpeed() = 0;
	}

	missile->SetPos({mX, mY});
}
