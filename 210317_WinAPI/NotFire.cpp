#include "NotFire.h"
void NotFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
       
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::NotSkillTYPE);
           
            // break;

        }
        
    }
}