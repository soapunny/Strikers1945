#include "MeteorFire.h"
#include "Missile.h"

void MeteorFire::DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    vector<Missile*>::iterator myIt;

     //���� ���� �ȿ��� ���� �� ��� �ø��� 
     //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));
    
    for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
    {
        if ((*myIt)->GetIsFired() == false)
        {   
            firedCount++;
            (*myIt)->SetType(Missile::SKILLTYPE::MeteorSkill_TYPE);
            (*myIt)->SetIsFired(true);            
            (*myIt)->SetAngle(DegToRad((firedCount * 3.14f * 2.0f / 36.0f)));
            
        }
    }
}