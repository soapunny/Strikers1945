#include "TornadoSkill.h"

void TornadoSkill::UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime) //매개변수 하나더 가져와야할거 같은데?
{
	//지그재그모양으로 아래를 향해 미사일 발사
	//도중에 미사일을 바꾸는건 어떻게하지?
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
	
	
		//if ((*iter)->GetIsFired() == false)
		//{
		//	angleCount++; //
		//	angleCount4++; //
		//	(*iter)->SetIsFired(true);
		//	(*iter)->SetAngle(-sin(angleCount / 8.0) / 5 - angleCount4 * 2);//  angleCount4이걸 잘 나누거나 곱하면 사방으로 튀는 특이한 패턴을 만들수잇따.
		//	break;
		//}
	

	(*pos).x += cos(*angle) * moveSpeed * elapsedTime / moveTime;
	(*pos).y -= sin(*angle) * moveSpeed * elapsedTime / moveTime;
}