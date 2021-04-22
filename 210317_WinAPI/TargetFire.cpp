#include "TargetFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void TargetFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    //   for (int j = 0; j < 5; j++)

           //������� �Ʒ��� ���ϴ� �̻��� ����
    for (auto lpMissile : *vMissiles)
    {
        if (lpMissile->GetIsFired() == false)
        {
            lpMissile->SetType(Missile::SKILLTYPE::TargetSkill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(-90));//������ ��������
            lpMissile->SetMoveSpeed(100 * (a+1));
            a++;
            if (a == 3)
            {
                a = 0;
                break;
            }
        }

    }

}