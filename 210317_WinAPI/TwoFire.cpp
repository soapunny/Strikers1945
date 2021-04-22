#include "TwoFire.h"
#include "Missile.h"
#include <ctime>
#include "CollisionCheck.h"
void TwoFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;


    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
    srand(std::time(NULL));

    int i = 0;
    for (auto lpMissile : *vMissiles)
    {

        if (lpMissile->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            lpMissile->SetType(Missile::SKILLTYPE::TwoSKill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(k));
            lpMissile->SetMoveSpeed(200);
            (this->collisionCheck)->SetBossMissile(lpMissile);

            i++;
            if(i >= 3)
                break;  
        }
         k+=20;
        if (k > -70) k = -110;
    }
}