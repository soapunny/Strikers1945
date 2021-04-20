#include "MeteorFire.h"
#include "Missile.h"
#include "CollisionCheck.h"

void MeteorFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
    vector<Missile*>::iterator myIt;

    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));
    for (int i = 0; i < 36; i++)
    {
       
        if (firedCount > 36) firedCount = 0;
        for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
        {

            if ((*myIt)->GetIsFired() == false)
            {
                firedCount++;
                (*myIt)->SetType(Missile::SKILLTYPE::MeteorSkill_TYPE);
                (*myIt)->SetIsFired(true);
                (*myIt)->SetAngle(DegToRad((firedCount * 10)));
                (*myIt)->SetMoveSpeed(170);
                break;

            }
        }
    }
}