#include "PlayerSkill.h"

void PlayerSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//������ ���� ���ϴ� �̻��� �߻�
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(DegToRad(missile->GetAngle())) * 3 * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	mY -= sin(DegToRad(missile->GetAngle())) * 3 * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
}

