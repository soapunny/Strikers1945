#include "MeteorFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void MeteorFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    this->collisionCheck = collisionCheck;
    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));
    for (int i = 0; i < 36; i++)
    {
       
        if (firedCount > 36) firedCount = 0;
        for (auto lpMissile : *vMissiles)
        {
            if (lpMissile->GetIsFired() == false)
            {
                firedCount++;
                lpMissile->SetType(Missile::SKILLTYPE::MeteorSkill_TYPE);
                lpMissile->SetIsFired(true);
                lpMissile->SetAngle(DegToRad((firedCount * 10)));
                lpMissile->SetMoveSpeed(170);
                (this->collisionCheck)->SetBossMissile(lpMissile);
                break;
            }
        }
    }
}