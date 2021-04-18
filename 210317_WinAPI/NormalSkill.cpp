#include "NormalSkill.h"
#include "Missile.h"

void NormalSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//일직선 아래로 향하는 미사일 발사
	missile->SetPos(
		FPOINT{
			(missile->GetPos().x + cosf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
			(missile->GetPos().y - sinf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
		}
	);
}
