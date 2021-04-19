#include "PlayerFire.h"
#include "Missile.h"

void PlayerFire::DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;
    // for (int j = 0; j < 5; j++)
    {
        //������ ���� ���ϴ� �̻��� ����
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {
            if ((*myIt)->GetIsFired() == false)
            {
                (*myIt)->SetType(Missile::SKILLTYPE::PlayerSkill_TYPE);
                (*myIt)->SetIsFired(true);
                break;
            }
        }
    }
}
