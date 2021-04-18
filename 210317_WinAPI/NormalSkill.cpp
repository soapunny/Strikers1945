#include "NormalSkill.h"
#include "Missile.h"

void NormalSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//������ �Ʒ��� ���ϴ� �̻��� �߻�
	missile->SetPos(
		FPOINT{
			(missile->GetPos().x + cosf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
			(missile->GetPos().y - sinf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
		}
	);
}
