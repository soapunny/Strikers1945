#include "TornadoSkill.h"

void TornadoSkill::UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime) //�Ű����� �ϳ��� �����;��Ұ� ������?
{
	//������׸������ �Ʒ��� ���� �̻��� �߻�
	//���߿� �̻����� �ٲٴ°� �������?
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	
		//if ((*iter)->GetIsFired() == false)
		//{
		//	angleCount++; //
		//	angleCount4++; //
		//	(*iter)->SetIsFired(true);
		//	(*iter)->SetAngle(-sin(angleCount / 8.0) / 5 - angleCount4 * 2);//  angleCount4�̰� �� �����ų� ���ϸ� ������� Ƣ�� Ư���� ������ ������յ�.
		//	break;
		//}
	

	(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;
}