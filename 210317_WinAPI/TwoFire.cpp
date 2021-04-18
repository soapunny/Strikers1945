#include "TwoFire.h"
void TwoFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;

    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
    srand(time(NULL));

    int i = 0;
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::TwoSKillTYPE);
            (*myIt)->SetIsFired(true);            
            (*myIt)->SetAngle(DegToRad(k));
            
            i++;
            if(i >= 2)
                break;
            
        }

         k+=10;
        if (k == -80) k = -100;
    }
}