#include "TwoFire.h"
#include "Missile.h"
#include <ctime>
#include "CollisionCheck.h"
void TwoFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;


    //���� ���� �ȿ��� ���� �� ��� �ø��� 
    //�۾����鼭 �ش� ��ġ�� ��� �׸��� �����
    srand(std::time(NULL));

    int i = 0;
    for (auto lpMissile : *vMissiles)
    {

        if (lpMissile->GetIsFired() == false)
        {
            randAngle = (rand() % 168 - 18) * 100;
            lpMissile->SetType(Missile::SKILLTYPE::TwoSKill_TYPE);
            lpMissile->SetIsFired(true);
            lpMissile->SetAngle(DegToRad(k));
            lpMissile->SetMoveSpeed(200);
            (this->collisionCheck)->SetBossMissile(lpMissile);

            i++;
            if(i >= 3)
                break;  
        }
         k+=20;
        if (k > -70) k = -110;
    }
}