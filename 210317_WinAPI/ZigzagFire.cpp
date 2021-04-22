#include "ZigzagFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void ZigzagFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
	this->collisionCheck = collisionCheck;

    vector<Missile*>::iterator myIt;
	//������� �Ʒ��� ���ϴ� �̻��� ����
	for (myIt = vMissiles->begin(); myIt != vMissiles->end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == false) //�����ν� Ȱ���ϱ����
		{
			(*myIt)->SetType(Missile::SKILLTYPE::ZigzagSkill_TYPE);
			(*myIt)->SetIsFired(true);
			(*myIt)->SetAngle(DegToRad(a * 3));//������ ��������
			(this->collisionCheck)->SetBossMissile((*myIt));
			break;
		}
		a++;
	}
}
