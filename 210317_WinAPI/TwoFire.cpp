#include "TwoFire.h"
#include <ctime>
void TwoFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));

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