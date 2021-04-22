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
        for (int i=0;i<vMissiles->size();i++)
        {

            if ((*vMissiles)[i]->GetIsFired() == false)
            {
                firedCount++;
                (*vMissiles)[i]->SetType(Missile::SKILLTYPE::MeteorSkill_TYPE);
                (*vMissiles)[i]->SetIsFired(true);
                (*vMissiles)[i]->SetAngle(DegToRad((firedCount * 10)));
                break;

            }
        }
    }
}