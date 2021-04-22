#include "FireworkSkill.h"
#include "Missile.h"

void FireworkSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	if (!isSkillReady) {
		if (missile->GetPos().y >= WINSIZE_Y / 6) {
			//missile->SetAngle(missile->GetAngle() + (elapsedTime * 2));
			missile->SetPos(
				FPOINT{
					(missile->GetPos().x + cosf(DegToRad(90)) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
					(missile->GetPos().y - sinf(DegToRad(90)) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
				}
			);
		}
		else {
			isSkillReady = true;
		}
	}
	else
	{
		time += elapsedTime;
		if(time < 1.0f){
			missile->SetPos(
				FPOINT{
					(missile->GetPos().x + cosf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
					(missile->GetPos().y - sinf(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
				}
			);
		}
		else {
			missile->SetPos(
				FPOINT{
					(missile->GetPos().x + cosf(DegToRad(-90)) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime()),
					(missile->GetPos().y - sinf(DegToRad(-90)) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime())
				}
			);
		}
	}

}
