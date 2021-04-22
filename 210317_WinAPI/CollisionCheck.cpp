#include "CollisionCheck.h"
#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Image.h"

HRESULT CollisionCheck::Init()
{
	keyCnt = 0;
	hitImg = ImageManager::GetSingleton()->FindImage("�� ���");
	if (hitImg == nullptr)
	{
		MessageBox(g_hWnd, "�� ��� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
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
	
	//"�÷��̾�"�� "���� �̻���" �浹
	for (myIt = bossMissile.begin(); myIt != bossMissile.end();)
	{
		if (IntersectRect(&rcTemp, &RectHit_Player, (*myIt)->GetEnemyMissileRect()))
		{
			playerIsCollision = true;
			(*myIt)->SetIsFired(false);
			myIt = bossMissile.erase(myIt);
		}
		else if (!(*myIt)->GetIsFired())
		{
			myIt = bossMissile.erase(myIt);
		}
		else
			myIt++;
	}

	//"�÷��̾� �̻���"�� "����"�浹
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
		else if (!(*myIt)->GetIsFired())
		{
			myIt = playerMissile.erase(myIt);
		}
		else
			myIt++;
	}

	/*if (IntersectRect(&rcTemp, &RectHit_Boss, &RectHit_Player))
	{
		playerIsCollision = true;
	}*/

	//"���� �̻���"�� "��ź"�浹
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


	//�Ŀ� Ȯ��/////////////////////////////
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
			//�÷��̾� �浹 �ڽ�
			RenderRect(hdc, RectHit_Player.left, RectHit_Player.top,
				RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);

			//�÷����� �̻��� �浹 �ڽ�
			for (auto lpMissile : playerMissile)
			{
				if (lpMissile->GetIsFired() == true)
				{
					RenderRectToCenter(hdc, (lpMissile->GetPlayerMissileRect()->left + lpMissile->GetPlayerMissileRect()->right) / 2,
						(lpMissile->GetPlayerMissileRect()->top + lpMissile->GetPlayerMissileRect()->bottom) / 2,
						(lpMissile->GetPlayerMissileRect()->right - lpMissile->GetPlayerMissileRect()->left),
						(lpMissile->GetPlayerMissileRect()->bottom - lpMissile->GetPlayerMissileRect()->top));
				}
			}

			//���� �浹 �ڽ�
			RenderRectToCenter(hdc, (RectHit_Boss.left + RectHit_Boss.right) / 2,
				(RectHit_Boss.top + RectHit_Boss.bottom) / 2,
				(RectHit_Boss.right - RectHit_Boss.left),
				(RectHit_Boss.bottom - RectHit_Boss.top));

			//���� �̻��� �浹 �ڽ�
			if (!isBossAlive)
				bossMissile.clear();
			for (auto lpMissile : bossMissile)
			{
				if (lpMissile->GetIsFired() == true)
				{
					RenderRectToCenter(hdc, 
						(lpMissile->GetEnemyMissileRect()->left + lpMissile->GetEnemyMissileRect()->right) / 2,
						(lpMissile->GetEnemyMissileRect()->top + lpMissile->GetEnemyMissileRect()->bottom) / 2,
						(lpMissile->GetEnemyMissileRect()->right - lpMissile->GetEnemyMissileRect()->left),
						(lpMissile->GetEnemyMissileRect()->bottom - lpMissile->GetEnemyMissileRect()->top));
				}
			}
		}
	}

	//�� ����Ʈ
	if (hitted)
		RendEffect(hdc, hitPos);

	//��ź �ݸ����ڽ�
	if (bombUse)
	{
		RenderRectToCenter(hdc, (RectHit_Bomb.left + RectHit_Bomb.right) / 2,
			(RectHit_Bomb.top + RectHit_Bomb.bottom) / 2,
			(RectHit_Bomb.right - RectHit_Bomb.left),
			(RectHit_Bomb.bottom - RectHit_Bomb.top));
	}
}
