#include "FallingKnivesSkill.h"
#include "Missile.h"

void FallingKnivesSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	time += elapsedTime;

	if (time < 1.0f) {
		missile->SetAngle(missile->GetAngle() + (elapsedTime * 2));
	}
	else if (time < 1.5f) {
		missile->SetAngle(missile->GetAngle() + 60 * PI * elapsedTime);
		missile->SetMoveSpeed(missile->GetMoveSpeed() + 500.0f * elapsedTime);
		return;
	}

	missile->SetPos(
		FPOINT{
			(missile->GetPos().x + cosf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
			(missile->GetPos().y - sinf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
		}
	);
}
