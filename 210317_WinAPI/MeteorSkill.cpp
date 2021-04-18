#include "MeteorSkill.h"
#include "Missile.h"

void MeteorSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//일직선 아래로 향하는 미사일 발사
	//srand(time(NULL));
	//moveSpeed = rand() % 50*10;	

	currTime++;

	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();	
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * missile->GetMoveSpeed() * elapsedTime / missile->GetMoveTime();

	if (currTime > 1)
	{
		//missile->SetMoveSpeed() = 0;
	}

	missile->SetPos({mX, mY});
}
