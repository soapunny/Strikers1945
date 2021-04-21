#include "SceneManager.h"
#include "Image.h"




void SceneManager::Render(HDC hdc)
{
	endingImage->Render(hdc);
}



void SceneManager::DeadNotify(bool OneBossAlive, bool twoBossAlive, bool threeBossAlive)
{
	if (OneBossAlive == false)
	{
		SetBossNumber(1);
	}
	else if (twoBossAlive == false)
	{
		SetBossNumber(2);
	}
	else if (threeBossAlive == false)
	{
		endingTrue = true;
		//엔딩하라 알려주기
	}
	
}


