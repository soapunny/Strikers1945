#include "CircularSkill.h"
#include "Missile.h"

void CircularSkill::UseSkill(Missile* missile)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	float x = missile->GetStartPos().x - mX;
	float y = missile->GetStartPos().y - mY;
	//float angle = missile->GetAngle();
	if (sqrt((x * x) + (y * y)) < 200)
	{
		mX += cosf(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
		mY -= sinf(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
	}
	missile->SetPos({ mX, mY });
}
