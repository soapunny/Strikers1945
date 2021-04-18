#include "WormFire.h"
void WormFire::DoFire(vector<Missile*>* vMissiles)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
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