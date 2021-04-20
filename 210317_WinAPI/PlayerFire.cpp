#include "PlayerFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void PlayerFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;
    vector<Missile*>::iterator myIt;
	//������ ���� ���ϴ� �̻��� ����
	for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == false)
		{
			(*myIt)->SetType(Missile::SKILLTYPE::PlayerSkill_TYPE);
			(*myIt)->SetIsFired(true);
			(this->collisionCheck)->SetPlayerMissile((*myIt));
			break;
		}
	}
}
