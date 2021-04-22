#include "TornadoFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void TornadoFire::DoFire(CollisionCheck* collisionCheck,vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    //������� �Ʒ��� ���ϴ� �̻��� ����
    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(a * 20));//������ ��������
            (this->collisionCheck)->SetBossMissile(lpMissile);
            a++;
            break;
        }
    }
}