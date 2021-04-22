#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
	this->collisionCheck = collisionCheck;

    vector<Missile*>::iterator myIt;
	//지그재그 아래로 향하는 미사일 장전
	for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == false) //난수로써 활용하기로함
		{
			(*myIt)->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
			(*myIt)->SetIsFired(true);
			(*myIt)->SetAngle(DegToRad(a * 3));//각각의 각도설정
			(this->collisionCheck)->SetBossMissile((*myIt));
			break;
		}
		a++;
	}
}
