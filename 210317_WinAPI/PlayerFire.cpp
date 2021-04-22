#include "PlayerFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void PlayerFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

	//일직선 위로 향하는 미사일 장전
	for (int i=0;i< vMissiles->size();i++)
	{
		if ((*vMissiles)[i]->GetIsFired() == false)
		{
			(*vMissiles)[i]->SetType(Missile::SKILLTYPE::PlayerSkill_TYPE);
			(*vMissiles)[i]->SetIsFired(true);
			(this->collisionCheck)->SetPlayerMissile((*vMissiles)[i]);
			break;
		}
	}
}
