#include "TornadoSkill.h"

void TornadoSkill::UseSkill(Missile* missile, FPOINT* lpTargetPos)
{
	//������׸������ �Ʒ��� ���� �̻��� �߻�
	//���߿� �̻����� �ٲٴ°� �������?
	 elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	// vector<Missile*>::iterator iter;
	//if ((*iter)->GetIsFired() == false)
	//	{
	//		angleCount++; //
	//		angleCount4++; //
	//		(*iter)->SetIsFired(true);
	//		(*iter)->SetAngle(-sin(angleCount / 8.0) / 5 - angleCount4 * 2);//  angleCount4�̰� �� �����ų� ���ϸ� ������� Ƣ�� Ư���� ������ ������յ�.
	//		break;
	//	}
	//

	/*(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;*/
}

