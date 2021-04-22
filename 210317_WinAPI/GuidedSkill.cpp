#include "GuidedSkill.h"
#include "Missile.h"

void GuidedSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//유도 미사일 발사
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float y = missile->GetPos().y - missile->GetPlayerPos().y;
	float x = - missile->GetPos().x + missile->GetPlayerPos().x;
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cosf(atan2(y, x)) * missile->GetMoveSpeed() * 1.5 * elapsedTime / missile->GetMoveTime();
	mY -= sinf(atan2(y, x)) * missile->GetMoveSpeed() * 1.5 * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
}