#include "ZigzagSkill.h"

void ZigzagSkill::UseSkill(Missile* missile)
{
	//������׸������ �Ʒ��� ���� �̻��� �߻�
	//���߿� �̻����� �ٲٴ°� �������?

	/*vector<Missile*>::iterator iter; //���� ������� ��ų 

	for (iter = vMissiles.begin(); iter != vMissiles.end(); iter++)
	{
		if ((*iter)->GetIsFired() == false)
		{

			if (angleCount < 10)
			{
				angleCount++;
				angle += 5;
				(*iter)->SetIsFired(true);
				(*iter)->SetAngle(DegToRad(angle));
			}
			else
			{
				angleCount++;
				angle -= 5;
				(*iter)->SetIsFired(true);
				(*iter)->SetAngle(DegToRad(angle));

			}
			break;
		}
	}
	if (angleCount == 20)
	{
		angleCount = 0;
	}*/
	//float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	//missileTimer += elapsedTime;
	////if (missileTimer  <1 ) //���� �̻��� Ÿ�ӿ� ���� �����Ѵ����� ����
	////{
	////	(*angle) = DegToRad (-45);
	////}
	////if (missileTimer  > 1)
	////{
	////	(*angle) = DegToRad(-135);
	////}

	//(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	//(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;
}
