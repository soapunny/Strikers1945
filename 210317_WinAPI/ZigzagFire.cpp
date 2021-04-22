#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    vector<Missile*>::iterator myIt;
 //   for (int j = 0; j < 5; j++)
    
        //������� �Ʒ��� ���ϴ� �̻��� ����
        for (int i =0;i<vMissiles->size();i++)
        {
            if ((*vMissiles)[i]->GetIsFired() == false) //�����ν� Ȱ���ϱ����
            {
                (*vMissiles)[i]->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
                (*vMissiles)[i]->SetIsFired(true);
                (*vMissiles)[i]->SetAngle(DegToRad(a*3));//������ ��������
                 
                break;   
            }
        a++;
        }
    
}
