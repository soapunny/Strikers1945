#include "GuidedFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void GuidedFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    time += 1.0f;
    vector<Missile*>::iterator myIt;
    if (time <= 30)
    {
        if (time < 10)
        {
            for (int j = 0; j < 9; j++)
            {
                //부채꼴
                for (int i =0;i<vMissiles->size();i++)
                {
                    if ((*vMissiles)[i]->GetIsFired() == false)
                    {
                        (*vMissiles)[i]->SetType(Missile::SKILLTYPE::CircularSkill_TYPE);
                        (*vMissiles)[i]->SetIsFired(true);
                        //float angle = DegToRad(-135 + 10 * j);
                        (*vMissiles)[i]->SetAngle(DegToRad(-135 + 10 * j));
                        break;
                    }
                }
            }
        }
    }
    else
    {
        //타겟 따라
        for (int i = 0; i < vMissiles->size(); i++)
        {
            if ((*vMissiles)[i]->GetType() == Missile::SKILLTYPE::CircularSkill_TYPE)
            {
                (*vMissiles)[i]->SetType(Missile::SKILLTYPE::Guided_Skill_TYPE);
            }
        }
    }
}