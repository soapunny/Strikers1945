#include "TornadoSkill.h"
#include "Missile.h"
void TornadoSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//������׸������ �Ʒ��� ���� �̻��� �߻�
	//���߿� �̻����� �ٲٴ°� �������?
	 elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	 float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	 float mX = missile->GetPos().x;
	 float mY = missile->GetPos().y;
	 mX += cos(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	 mY -= sin(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	 missile->SetPos({ mX, mY });

}

