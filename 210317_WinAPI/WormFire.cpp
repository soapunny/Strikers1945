#include "WormFire.h"
void WormFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;

    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
    srand(std::time(NULL));

    
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::WormSKillTYPE);
            (*myIt)->SetIsFired(true);
            (*myIt)->SetAngle((k * 3.14f * 2.0f / 36.0f));
            break;
        }
        k++;
    }
}