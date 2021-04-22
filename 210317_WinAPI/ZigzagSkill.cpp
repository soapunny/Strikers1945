#include "ZigzagSkill.h"
#include "Missile.h"

void ZigzagSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	float mX = missile->GetPos().x;
	float mY = missile->GetPos().y;
	mX += cos(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	mY -= sin(missile->GetAngle()) * (missile->GetMoveSpeed()) * elapsedTime / missile->GetMoveTime();
	missile->SetPos({ mX, mY });
	//지그재그모양으로 아래를 향해 미사일 발사
	//도중에 미사일을 바꾸는건 어떻게하지?

	/*vector<Missile*>::iterator iter; //기존 지그재그 스킬

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
	////if (missileTimer  <1 ) //내일 미사일 타임에 대해 연구한다음에 하자
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
