#include "GuidedFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void GuidedFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    time += 1.0f;
    vector<Missile*>::iterator myIt;
    if (time <= 30)
    {
        if (time < 10)
        {
            for (int j = 0; j < 9; j++)
            {
                //부채꼴
                for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
                {
                    if ((*myIt)->GetIsFired() == false)
                    {
                        (*myIt)->SetType(Missile::SKILLTYPE::CircularSkill_TYPE);
                        (*myIt)->SetIsFired(true);
                        (this->collisionCheck)->SetBossMissile((*myIt));
                        //float angle = DegToRad(-135 + 10 * j);
                        (*myIt)->SetAngle(DegToRad(-135 + 10 * j));
                        break;
                    }
                }
            }
        }
    }
    else
    {
        //타겟 따라
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetType() == Missile::SKILLTYPE::CircularSkill_TYPE)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::Guided_Skill_TYPE);
                (this->collisionCheck)->SetBossMissile((*myIt));
            }
        }
    }
}