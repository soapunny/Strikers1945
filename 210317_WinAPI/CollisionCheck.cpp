#include "CollisionCheck.h"
#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "Image.h"
#include "Enemy.h"
#include "Item.h"

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

	//playerAttackValue = 1;

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
	list<Enemy*>::iterator myIt2;
	list<Item*>::iterator myIt3;
	
	//"�÷��̾�"�� "���� �̻���" �浹
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

	//"�÷��̾� �̻���"�� "����" �浹
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

	//"���� �̻���"�� "��ź" �浹
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

	//"�÷��̾�"�� "������" �浹
	for (myIt3 = itemData.begin(); myIt3 != itemData.end();)
	{
		if (IntersectRect(&rcTemp, &RectHit_Player, (*myIt3)->GetItemRect()))
		{
			(*myIt3)->SetIsFired(false);
			myIt3 = itemData.erase(myIt3);

			//1�� power, 2�� bomb, 3�� life
			if (item == 2)
			{
				powerIsCollision = true;
			}
			if (item == 3)
			{
				bombIsCollision = true;
			}
			if (item == 1)
			{
				lifeIsCollision = true;
			}
		}
		else
			myIt3++;
	}

	//"�÷��̾� �̻���"�� "���/���ʹ�" �浹
	for (myIt2 = enemyData.begin(); myIt2 != enemyData.end();)
	{
		for (myIt = playerMissile.begin(); myIt != playerMissile.end();)
		{
			if (IntersectRect(&rcTemp, (*myIt2)->GetEnemyRect(), (*myIt)->GetPlayerMissileRect()))
			{
				bossMissile.clear();
				(*myIt)->SetIsFired(false);
				(*myIt)->SetPlayerMissileRect({ -100, -100, -100, -100 });
				(*myIt2)->SetIsAlive(false);
				(*myIt2)->SetEnemyRectZero();
				hitted = true;
				hitPos = { (float)((*myIt)->GetPlayerMissileRect()->left), (float)((*myIt)->GetPlayerMissileRect()->top) };
				myIt = playerMissile.erase(myIt);
				myIt2 = enemyData.erase(myIt2);
			}
			else
				myIt++;
		}
		myIt2 ++;
	}

	//�Ŀ� Ȯ��/////////////////////////////
	//if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	//{
	//	bombIsCollision = true;
	//	//lifeIsCollision = true;
	//}
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
	////if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
	//{
	//	//keyCnt++;
	//	//if (keyCnt % 2 == 1)
	//	{
	//		//�÷��̾� �浹 �ڽ�
	//		RenderRect(hdc, RectHit_Player.left, RectHit_Player.top,
	//			RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);

	//		//�÷����� �̻��� �浹 �ڽ�
	//		for (auto lpMissile : playerMissile)
	//		{
	//			if (lpMissile->GetIsFired() == true)
	//			{
	//				RenderRectToCenter(hdc, (lpMissile->GetPlayerMissileRect()->left + lpMissile->GetPlayerMissileRect()->right) / 2,
	//					(lpMissile->GetPlayerMissileRect()->top + lpMissile->GetPlayerMissileRect()->bottom) / 2,
	//					(lpMissile->GetPlayerMissileRect()->right - lpMissile->GetPlayerMissileRect()->left),
	//					(lpMissile->GetPlayerMissileRect()->bottom - lpMissile->GetPlayerMissileRect()->top));
	//			}
	//		}

	//		//���� �浹 �ڽ�
	//		RenderRectToCenter(hdc, (RectHit_Boss.left + RectHit_Boss.right) / 2,
	//			(RectHit_Boss.top + RectHit_Boss.bottom) / 2,
	//			(RectHit_Boss.right - RectHit_Boss.left),
	//			(RectHit_Boss.bottom - RectHit_Boss.top));

	//		//���� �̻��� �浹 �ڽ�
	//		if (!isBossAlive)
	//			bossMissile.clear();
	//		for (auto lpMissile : bossMissile)
	//		{
	//			if (lpMissile->GetIsFired() == true)
	//			{
	//				RenderRectToCenter(hdc,
	//					(lpMissile->GetEnemyMissileRect()->left + lpMissile->GetEnemyMissileRect()->right) / 2,
	//					(lpMissile->GetEnemyMissileRect()->top + lpMissile->GetEnemyMissileRect()->bottom) / 2,
	//					(lpMissile->GetEnemyMissileRect()->right - lpMissile->GetEnemyMissileRect()->left),
	//					(lpMissile->GetEnemyMissileRect()->bottom - lpMissile->GetEnemyMissileRect()->top));
	//			}
	//			else
	//			{
	//				RenderRectToCenter( hdc , -100, -100, -100 , -100);
	//			}
	//		}

	//		//��� �浹 �ڽ�
	//		//if (!isEnemyAlive)
	//			//enemyData.clear();
	//		for (auto lpRECT : enemyData)
	//		{
	//			if (lpRECT->GetIsAlive() == true)
	//			{
	//				RenderRectToCenter(hdc,
	//					(lpRECT->GetEnemyRect()->left + lpRECT->GetEnemyRect()->right) / 2,
	//					(lpRECT->GetEnemyRect()->top + lpRECT->GetEnemyRect()->bottom) / 2,
	//					(lpRECT->GetEnemyRect()->right - lpRECT->GetEnemyRect()->left),
	//					(lpRECT->GetEnemyRect()->bottom - lpRECT->GetEnemyRect()->top));
	//			}
	//		}

	//		//������ �浹 �ڽ�
	//		for (auto lpItem : itemData)
	//		{
	//			if (lpItem->GetIsFired() == true)
	//			{
	//				RenderRectToCenter(hdc,
	//					(lpItem->GetItemRect()->left + lpItem->GetItemRect()->right) / 2,
	//					(lpItem->GetItemRect()->top + lpItem->GetItemRect()->bottom) / 2,
	//					(lpItem->GetItemRect()->right - lpItem->GetItemRect()->left),
	//					(lpItem->GetItemRect()->bottom - lpItem->GetItemRect()->top));
	//			}
	//		}

	//		//�� ����Ʈ
	//		if (hitted)
	//			RendEffect(hdc, hitPos);

	//		//��ź �ݸ����ڽ�
	//		if (bombUse)
	//		{
	//			RenderRectToCenter(hdc, (RectHit_Bomb.left + RectHit_Bomb.right) / 2,
	//				(RectHit_Bomb.top + RectHit_Bomb.bottom) / 2,
	//				(RectHit_Bomb.right - RectHit_Bomb.left),
	//				(RectHit_Bomb.bottom - RectHit_Bomb.top));
	//		}
	//	}
	//}
}

void CollisionCheck::DeleteEnemyMissile(Missile* missile)
{
	
}
