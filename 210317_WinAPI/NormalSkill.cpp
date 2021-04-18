#include "NormalSkill.h"
#include "Missile.h"

void NormalSkill::UseSkill(Missile* missile)//FPOINT* pos, float* angle, float moveSpeed, float moveTime)
{
	//������ �Ʒ��� ���ϴ� �̻��� �߻�
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
}

