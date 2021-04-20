#include "FallingKnivesFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void FallingKnivesFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator it;
    int fireCnt = 12;
    //int fireCnt = 6;

    for (it = vMissiles->begin(); it != vMissiles->end(); it++)
    {
        if ((*it)->GetIsFired() == false)
        {
            (*it)->SetType(Missile::SKILLTYPE::FallingKnives_TYPE);
            //(*it)->SetType(Missile::TYPE::Zigzag);

            //(*it)->SetPos(FPOINT{ owner->GetPos().x, owner->GetPos().y });
            //(*it)->SetPos(FPOINT{(float)(owner->GetPos().x + fireCnt*40 * pow(-1, fireCnt)), owner->GetPos().y });
            //(*it)->SetAngle(DegToRad(-60*fireCnt));
            (*it)->SetAngle(DegToRad(-30 * fireCnt));

            (*it)->SetIsFired(true);
            fireCnt--;
            if (fireCnt <= 0) break;
        }
    }
}
