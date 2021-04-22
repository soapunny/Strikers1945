#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
	this->collisionCheck = collisionCheck;


 //   for (int j = 0; j < 5; j++)
    
        //������� �Ʒ��� ���ϴ� �̻��� ����
        for (auto lpMissile : *vMissiles)
        {
            if (lpMissile->GetIsFired() == false) //�����ν� Ȱ���ϱ����
            {
                lpMissile->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
                lpMissile->SetIsFired(true);
                lpMissile->SetAngle(DegToRad(a*3));//������ ��������
                 
			    (this->collisionCheck)->SetBossMissile(lpMissile);
			break;
		    }
		    a++;
	    }
}
