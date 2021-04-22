#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
	this->collisionCheck = collisionCheck;


 //   for (int j = 0; j < 5; j++)
    
        //지그재그 아래로 향하는 미사일 장전
        for (auto lpMissile : *vMissiles)
        {
            if (lpMissile->GetIsFired() == false) //난수로써 활용하기로함
            {
                lpMissile->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
                lpMissile->SetIsFired(true);
                lpMissile->SetAngle(DegToRad(a*3));//각각의 각도설정
                 
			    (this->collisionCheck)->SetBossMissile(lpMissile);
			break;
		    }
		    a++;
	    }
}
