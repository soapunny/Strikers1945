#include "TornadoSkill.h"
#include "Missile.h"
void TornadoSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//지그재그모양으로 아래를 향해 미사일 발사
	//도중에 미사일을 바꾸는건 어떻게하지?
	 elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	 float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	 float mX = missile->GetPos().x;
	 float mY = missile->GetPos().y;
	 mX += cos(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	 mY -= sin(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	 missile->SetPos({ mX, mY });

}

