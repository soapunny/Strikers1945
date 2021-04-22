#include "GuidedFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void GuidedFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    time += 1.0f;

    if (time <= 30)
    {
        if (time < 10)
        {
            for (int j = 0; j < 9; j++)
            {
                //부채꼴
                for (auto lpMissile : *vMissiles)
                {
                    if (lpMissile->GetIsFired() == false)
                    {
                        lpMissile->SetType(Missile::SKILLTYPE::CircularSkill_TYPE);
                        lpMissile->SetIsFired(true);
                        (this->collisionCheck)->SetBossMissile(lpMissile);

                        //float angle = DegToRad(-135 + 10 * j);
                        lpMissile->SetAngle(DegToRad(-135 + 10 * j));
                        break;
                    }
                }
            }
        }
    }
    else
    {
        //타겟 따라
        for (auto lpMissile : *vMissiles)
        {
            if (lpMissile->GetType() == Missile::SKILLTYPE::CircularSkill_TYPE)
            {

                lpMissile->SetType(Missile::SKILLTYPE::Guided_Skill_TYPE);
                (this->collisionCheck)->SetBossMissile(lpMissile);
            }
        }
    }
}