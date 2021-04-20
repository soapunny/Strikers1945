#include "TornadoFire.h"
#include "Missile.h"
void TornadoFire::DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;
    //   for (int j = 0; j < 5; j++)

           //������� �Ʒ��� ���ϴ� �̻��� ����
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {
            (*myIt)->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
            (*myIt)->SetIsFired(true);
            (*myIt)->SetAngle(DegToRad(a * 20));//������ ��������
            a++;
            break;
        }
       
    }

}