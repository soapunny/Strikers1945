#include "NormalFire.h"
#include "Missile.h"

void NormalFire::DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    vector<Missile*>::iterator myIt;
    for (int j = 0; j < 5; j++)
    {
        //������ �Ʒ��� ���ϴ� �̻��� ����
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::NormalSkillTYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(DegToRad(-90));
                break;
            }
        }
    }
}
