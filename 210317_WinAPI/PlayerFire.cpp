#include "PlayerFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void PlayerFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

	//������ ���� ���ϴ� �̻��� ����
	for (auto lpMissile : *vMissiles)
	{
		if (lpMissile->GetIsFired() == false)
		{
			lpMissile->SetType(Missile::SKILLTYPE::PlayerSkill_TYPE);
			lpMissile->SetIsFired(true);
			(this->collisionCheck)->SetPlayerMissile(lpMissile);
			break;
		}
	}
}
