#include "CollisionCheck.h"
#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Image.h"

HRESULT CollisionCheck::Init()
{
	keyCnt = 0;
	hitImg = ImageManager::GetSingleton()->FindImage("힛 모션");
	if (hitImg == nullptr)
	{
		MessageBox(g_hWnd, "힛 모션 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}
	frameCount = 0;
	currFrameX = 0;
	time = 0;

	hitted = false;

	playerAttackValue = 1;

	bombUse = false;

	playerIsCollision = false;
	bossIsCollision = false;

	return S_OK;
}

void CollisionCheck::Release()
{
}

void CollisionCheck::Update()
{
	list<Missile*>::iterator myIt;
	
	//"플레이어"와 "보스 미사일" 충돌
	for (myIt = bossMissile.begin(); myIt != bossMissile.end();)
	{
		if (IntersectRect(&rcTemp, &RectHit_Player, (*myIt)->GetEnemyMissileRect()))
		{
			playerIsCollision = true;
			(*myIt)->SetIsFired(false);
			myIt = bossMissile.erase(myIt);
		}
		else
			myIt++;
	}

	//"플레이어 미사일"과 "보스"충돌
	for (myIt = playerMissile.begin(); myIt != playerMissile.end();)
	{
		if (IntersectRect(&rcTemp, &RectHit_Boss, (*myIt)->GetPlayerMissileRect()))
		{
			bossIsCollision = true;
			(*myIt)->SetIsFired(false);
			hitted = true;
			hitPos = { (float)((*myIt)->GetPlayerMissileRect()->left), (float)((*myIt)->GetPlayerMissileRect()->top) };
			myIt = playerMissile.erase(myIt);
		}
		else
			myIt++;
	}

	/*if (IntersectRect(&rcTemp, &RectHit_Boss, &RectHit_Player))
	{
		playerIsCollision = true;
	}*/

	//"보스 미사일"과 "폭탄"충돌
	if (bombUse)
	{
		for (myIt = bossMissile.begin(); myIt != bossMissile.end();)
		{
			if (IntersectRect(&rcTemp, &RectHit_Bomb, (*myIt)->GetEnemyMissileRect()))
			{
				(*myIt)->SetIsFired(false);
				myIt = bossMissile.erase(myIt);
			}
			else
				myIt++;
		}
	}


	//파워 확인/////////////////////////////
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		if (playerAttackValue <= 2)
		{
			playerAttackValue += 1;
		}
	}
	
	
}

void CollisionCheck::RendEffect(HDC hdc, FPOINT pos)
{
	hitImg->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, false);

	time += TimerManager::GetSingleton()->getElapsedTime();
	if (time > 0.1f)
	{
		if (currFrameX < 6)
			currFrameX++;
		else
		{
			currFrameX = 0;
			hitted = false;
		}
		time = 0;
	}
}

void CollisionCheck::Render(HDC hdc)
{
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	{
		//keyCnt++;
		//if (keyCnt % 2 == 1)
		{
			//플레이어 충돌 박스
			RenderRect(hdc, RectHit_Player.left, RectHit_Player.top,
				RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);

			//플레리어 미사일 충돌 박스
			list<Missile*>::iterator myIt;
			for (myIt = playerMissile.begin(); myIt != playerMissile.end(); myIt++)
			{
				if ((*myIt)->GetIsFired() == true)
				{
					RenderRectToCenter(hdc, ((*myIt)->GetPlayerMissileRect()->left + (*myIt)->GetPlayerMissileRect()->right) / 2,
						((*myIt)->GetPlayerMissileRect()->top + (*myIt)->GetPlayerMissileRect()->bottom) / 2,
						((*myIt)->GetPlayerMissileRect()->right - (*myIt)->GetPlayerMissileRect()->left),
						((*myIt)->GetPlayerMissileRect()->bottom - (*myIt)->GetPlayerMissileRect()->top));
				}
			}

			//보스 충돌 박스
			RenderRectToCenter(hdc, (RectHit_Boss.left + RectHit_Boss.right) / 2,
				(RectHit_Boss.top + RectHit_Boss.bottom) / 2,
				(RectHit_Boss.right - RectHit_Boss.left),
				(RectHit_Boss.bottom - RectHit_Boss.top));

			//보스 미사일 충돌 박스
			if (!isBossAlive)
				bossMissile.clear();
			for (myIt = bossMissile.begin(); myIt != bossMissile.end(); myIt++)
			{
				if ((*myIt)->GetIsFired() == true)
				{
					RenderRectToCenter(hdc, ((*myIt)->GetEnemyMissileRect()->left + (*myIt)->GetEnemyMissileRect()->right) / 2,
						((*myIt)->GetEnemyMissileRect()->top + (*myIt)->GetEnemyMissileRect()->bottom) / 2,
						((*myIt)->GetEnemyMissileRect()->right - (*myIt)->GetEnemyMissileRect()->left),
						((*myIt)->GetEnemyMissileRect()->bottom - (*myIt)->GetEnemyMissileRect()->top));
				}
			}
		}
	}

	//힛 이펙트
	if (hitted)
		RendEffect(hdc, hitPos);

	//폭탄 콜리젼박스
	if (bombUse)
	{
		RenderRectToCenter(hdc, (RectHit_Bomb.left + RectHit_Bomb.right) / 2,
			(RectHit_Bomb.top + RectHit_Bomb.bottom) / 2,
			(RectHit_Bomb.right - RectHit_Bomb.left),
			(RectHit_Bomb.bottom - RectHit_Bomb.top));
	}
}
