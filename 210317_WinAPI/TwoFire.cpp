#include "TwoFire.h"
void TwoFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(time(NULL));

    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            (*myIt)->SetType(Missile::SKILLTYPE::TwoSKillTYPE);
            (*myIt)->SetIsFired(true);            
            (*myIt)->SetAngle(DegToRad(k));
            // break;
            
        }

         k+=10;
        if (k == -80) k = -100;
    }
}