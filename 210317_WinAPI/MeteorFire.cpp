#include "MeteorFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void MeteorFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    this->collisionCheck = collisionCheck;
    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
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