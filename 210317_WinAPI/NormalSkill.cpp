#include "NormalSkill.h"
#include "Missile.h"

void NormalSkill::UseSkill(Missile* missile)//FPOINT* pos, float* angle, float moveSpeed, float moveTime)
{
	//일직선 아래로 향하는 미사일 발사
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
}

