#include "ZigzagFire.h"
#include "Missile.h"
void ZigzagFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;
 //   for (int j = 0; j < 5; j++)
    {
        //������� �Ʒ��� ���ϴ� �̻��� ����
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::ZigzagSkillTYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(DegToRad(a*10));//������ ��������
                break;
            }
            a++;
        }
    }
}