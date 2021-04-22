#include "NormalFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void NormalFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{

    //������ �Ʒ��� ���ϴ� �̻��� ����
    this->collisionCheck = collisionCheck;

    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::NormalSkill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(-90));
            (this->collisionCheck)->SetBossMissile(lpMissile);
            break;
        }
    }
}
