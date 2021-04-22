#include "CircularSkill.h"
#include "Missile.h"

void CircularSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//ºÎÃ¤²Ã
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	float x = missile->GetStartPos().x - mX;
	float y = missile->GetStartPos().y - mY;
	if (sqrt((x * x) + (y * y)) < 200)
	{
		mX += cosf(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
		mY -= sinf(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
	}
	missile->SetPos({ mX, mY });
}
