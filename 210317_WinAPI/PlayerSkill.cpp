#include "PlayerSkill.h"

void PlayerSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//������ ���� ���ϴ� �̻��� �߻�
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * 2 * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * 2 * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
}

