#include "GuidedFire.h"
#include "Missile.h"

void GuidedFire::DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
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
                for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
                {
                    if ((*myIt)->GetIsFired() == false)
                    {
                        (*myIt)->SetType(Missile::SKILLTYPE::CircularSkillTYPE);
                        (*myIt)->SetIsFired(true);
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
            if ((*myIt)->GetType() == Missile::SKILLTYPE::CircularSkillTYPE)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::GuidedSkillTYPE);
            }
        }
    }
}