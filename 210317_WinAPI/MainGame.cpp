#pragma once
#include "MainGame.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Image.h"
#include "PlayerShip.h"
#include "BossManager.h"
#include "ItemManager.h"
#include "CollisionCheck.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);
	status = 0;
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	//�̹����� �̸� �ε� �ص���
	ImageManager::GetSingleton()->AddImage("Enemy","Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("SmallEnemy", "Image/Enemy1.bmp", 320, 426, 1, 1, true, RGB(0, 255, 0));
	ImageManager::GetSingleton()->AddImage("MediumEnemy", "Image/Enemy2.bmp", 265, 355, 1, 1, true, RGB(0, 248, 0));
	ImageManager::GetSingleton()->AddImage("BigEnemy", "Image/Enemy3.bmp", 252, 374, 1, 1, true, RGB(0, 248, 0));
	ImageManager::GetSingleton()->AddImage("����", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/����.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� ������ ���ּ�", "Image/blinkPlayer.bmp", 489 / 6, 131 / 2, 1, 1, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("�� �̻���", "Image/bullet(5)_white.bmp", 25, 25, true, RGB(255, 255, 255));
	//ImageManager::GetSingleton()->AddAngleImage("�÷��̾� �̻���(1)","Image/bullet(6).bmp", 31, 53, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddAngleImage("�÷��̾� �̻���(2)", "Image/bullet(7).bmp", 31, 52, true, RGB(255, 0, 255));
	//ImageManager::GetSingleton()->AddAngleImage("�÷��̾� �̻���(3)", "Image/bullet(8).bmp", 31, 53, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���(1)","Image/bullet(6).bmp", 31, 53, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���(2)", "Image/bullet(7).bmp", 31, 52, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���(3)", "Image/bullet(8).bmp", 31, 53, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���(3)_L", "Image/bullet(8)_L.bmp", 44, 46, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���(3)_R", "Image/bullet(8)_R.bmp", 44, 46, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� ���ּ�", "Image/playerJet.bmp", 489/3*2, 131/3*2, 3, 1, true, RGB(248, 0, 248));

	ImageManager::GetSingleton()->AddImage("StageTwoBoss", "Image/StageTwoBoss.bmp", 3152*2, 156*2,16,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageThreeBoss", "Image/StageThreeBoss.bmp", 163 * 24, 121, 24, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("�й迣��", "Image/gameover.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("��������", "Image/BossExplosion(16).bmp", 1019*2, 63*2, 16, 1, true, RGB(0, 248, 0));
	ImageManager::GetSingleton()->AddImage("�������", "Image/miniEnemyExplosion(12).bmp", 384, 32, 12, 1, true, RGB(0, 248, 0));
	ImageManager::GetSingleton()->AddImage("Ÿ�̸�", "Image/timer.bmp", 535, 82, 10, 1, true, RGB(67, 77, 112));
	/*ImageManager::GetSingleton()->AddImage("����1����", "Image/onebossEnding.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(67, 77, 112));
	ImageManager::GetSingleton()->AddImage("����2����", "Image/twobossEnding.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(67, 77, 112));
	ImageManager::GetSingleton()->AddImage("����3����", "Image/threebossEnding.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(67, 77, 112));*/
	ImageManager::GetSingleton()->AddImage("����", "Image/Ending.bmp", WINSIZE_X*3, WINSIZE_Y, 3, 1, true, RGB(67, 77, 112));
	ImageManager::GetSingleton()->AddImage("������", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("������������", "Image/Life.bmp", 820/10, 793/10,true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("��ź������", "Image/bombItem.bmp", 216, 32, 4, 1, true, RGB(0, 128, 128));
	ImageManager::GetSingleton()->AddImage("�Ŀ�������", "Image/powerItem.bmp", 150, 18, 6, 1, true, RGB(0, 128, 128));
	//ImageManager::GetSingleton()->AddImage("����", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("�� ���", "Image/hitEffect.bmp", 209 * 2, 36 * 2, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("���� ������ ���", "Image/itemExplotion(12).bmp", 1536*2.5, 128*2.5, 12, 1, true, RGB(0, 248, 0));
	
	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//isItemMake[10] = false;
	oneTimeDrop[0] = false;
	oneTimeDrop[1] = false;
	oneTimeDrop[2] = false;

	//�ɼ��� ���
	sceneManagerObserver = new SceneManager;
	RegisterObserver(sceneManagerObserver);

	//��� �̹���
	backGround = new Image();
	backGround->Init("Image/backGround(3).bmp", WINSIZE_X, 1887);
	backGroundPos.x = 0;
	backGroundPos.y = -1887 + WINSIZE_Y;
	backCloud = new Image();
	backCloud = ImageManager::GetSingleton()->FindImage("����");
	openingImage = ImageManager::GetSingleton()->FindImage("������");
	endingImage = ImageManager::GetSingleton()->FindImage("����");
	//endingTimerImage = ImageManager::GetSingleton()->FindImage("Ÿ�̸�");
	hundredSecondImg = ImageManager::GetSingleton()->FindImage("Ÿ�̸�");
	tenSecondImg = ImageManager::GetSingleton()->FindImage("Ÿ�̸�");
	oneSecondImg = ImageManager::GetSingleton()->FindImage("Ÿ�̸�");
	
	//��ũ
	tank = new Tank();
	tank->Init();

	//�浹
	collisionCheck = new CollisionCheck();
	collisionCheck->Init();

	//�÷��̾�
	playerShip = new PlayerShip();
	playerShip->Init(collisionCheck);
	
	// ���ʹ� �޴���
	enemyManager = new EnemyManager();
	enemyManager->Init(collisionCheck);

	//����
	bossManager = new BossManager();
	bossManager->Init(collisionCheck, playerShip->GetLpPos());

	////������
	vItemManager.resize(10);
	for (int i = 0; i < vItemManager.size(); i++)
	{
		vItemManager[i] = new ItemManager;
		vItemManager[i]->Init(collisionCheck);
	}

	//�ʱ�ȭ Ȯ��
	isInited = true;

	itemTime = 0;
	currFrame = 0;

	hundredSecond=0;
	tenSecond=0;
	oneSecond=0;
	onetimesave = true;

	return S_OK;
}

void MainGame::Release()
{
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(backGround);
	SAFE_RELEASE(tank);
	SAFE_RELEASE(enemyManager);
	SAFE_RELEASE(playerShip);
	SAFE_RELEASE(bossManager);
	SAFE_RELEASE(collisionCheck);

	
	ReleaseDC(g_hWnd, hdc);

	//KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	//��� �̵�
	if (status >= 1)
	{
		backGroundPos.y += elapsedTime * 100.0f;
		if (backGroundPos.y >= 0)
		{
			backGroundPos.y = -1887 + WINSIZE_Y;
		}

		//��ũ(�÷��̾�)
		if (tank)
		{
			tank->Update();
		}

		//��
		if (enemyManager)
		{
			enemyManager->SetPlayerPos(playerShip->GetPos());
			enemyManager->Update();
		}

		//�÷��̾�
		if (playerShip)
		{
			playerShip->SetPlayerAttackValue(collisionCheck->GetPlayerAttackValue());
			playerShip->Update();
		}

		//����
		if (bossManager)
		{
			bossManager->SetAttackValue(playerShip->GetPlayerAttackValue());
			bossManager->Update();
		}

		//�� �÷��̾� �浹 �˻�
		if (collisionCheck)
		{
			collisionCheck->Update();
			CheckCollision();
		}
		ItemMake();
		
		//for (int i = 0; i < vItemManager.size(); i++)
		{			
			vItemManager[1]->Update();
		}
	} 
		//status = sceneManagerObserver->GetNextStatus();	
}

void MainGame::Render()
 {
	HDC hBackDC = backBuffer->GetMemDC();
	if (status == 0)//������ ����
	{ 
  		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			status++;
			//sceneManagerObserver->OpeningNotify(status);
			//������ �ѱ��
		}
		if (openingImage)
		{
			openingImage->Render(hBackDC);
		}
	}
	else if (status == 1)
	{
	//���
		if (backGround)
		{
			backGround->Render(hBackDC, backGroundPos.x, backGroundPos.y);
		}
		if (backCloud)
		{
			//backCloud->AlphaRender(hBackDC, backGroundPos.x, backGroundPos.y);

			//BLENDFUNCTION* blendFunc = backCloud->GetBlendFunc();
			//blendFunc->SourceConstantAlpha = 100;
		}
		
		//FPS
		TimerManager::GetSingleton()->Render(hBackDC);


		//collsion
		if (collisionCheck) 
		{
			collisionCheck->Render(hBackDC);
		}

		//for (int i = 0; i < vItemManager.size(); i++)
		{
			//if(vItemManager[i])
			//if (vItemManager[1]->GetIsItem())
			{

				vItemManager[1]->Render(hBackDC);
				//vItemManager[1]->SetIsItem(false);
			}
				
		}
		//tank
		if (tank)
		{
			//tank->Render(hBackDC);
		}

		//enemy manager
		if (enemyManager)
		{
			enemyManager->Render(hBackDC);
		}

		//playerShip
		if (playerShip)
		{
			playerShip->Render(hBackDC);
		}
	
		//boss Manager
		if (bossManager)  //������ �������� �����ְ� 
		{
			bossManager->Render(hBackDC);
		}

		if (bossManager->GetEnding() == true)
		{
			status =2;
		}
	}
	else if(status == 2)//���� ���
	{
		/*endingImage = ImageManager::GetSingleton()->FindImage("����1����");
		endingImage = ImageManager::GetSingleton()->FindImage("����2����");
		endingImage = ImageManager::GetSingleton()->FindImage("����3����");*/

				
		//endElaspedTimer = TimerManager::GetSingleton()->getElapsedTime();
		//endTimer += endElaspedTimer;

		endTimer++;//���� Ÿ�̸Ӱ� ������ ������ ����?

		//if ((int)endTimer%2 ==0) //ending Ÿ�̸�
		//{
		//	
		//}
		if (endTimer >= 200)
		{
			currFrame ++;
			endTimer = 0;

		}
		

		if (endingImage)
		{
			if (currFrame == 3)
			{
				currFrame = 0;
			}
			endingImage->FrameRender(hBackDC,0,0,currFrame,0,false);
		}

		if (onetimesave)
		{
			endingTime = TimerManager::GetSingleton()->getGameSecond();
			onetimesave = false;
		}
		 //�ѹ��� �ʱ�ȭ �Ϸ��� ����ƽ����?

		hundredSecond = endingTime / 100 ;
		tenSecond = (endingTime % 100) / 10 ;
		oneSecond = endingTime % 10 ;
		

		hundredSecondImg->FrameRender(hBackDC, 400, 600, hundredSecond, 0, true);
		tenSecondImg->FrameRender(hBackDC, 450, 600, tenSecond, 0, true);
		oneSecondImg->FrameRender(hBackDC, 500, 600, oneSecond, 0, true);
	}
	

	backBuffer->Render(hdc);
}

void MainGame::RegisterObserver(SceneManager* scenemanager)
{
	sceneManagerObserver = scenemanager;
}



void MainGame::UnRegisterObserver()
{
	delete sceneManagerObserver;
	sceneManagerObserver = nullptr;
}

void MainGame::notifyObserve()
{

}

void MainGame::CheckCollision()
{
	//"�÷��̾�"�� "���� �̻���"�� �⵿�ߴٸ�
	if (collisionCheck->GetPlayerCollision())
	{
		playerShip->SetPlayerLife();				//�÷��̾� ��� �ϳ� ���̱�
		collisionCheck->SetPlayerCollision(false);
	}

	//"�÷��̾� �̻���"�� "����"�� �⵿�ߴٸ�
	if (collisionCheck->GetBossCollision())
	{
		bossManager->SetBossLife();				//���� ��� ������
		collisionCheck->SetBossCollision(false);
	}
	//�÷��̾� Life�߰�
	if (KeyManager::GetSingleton()->IsOnceKeyUp('H'))
	{
		playerShip->SetPlusPlayerLife();
	}

	
}

void MainGame::ItemMake()
{
	srand(time(NULL));
	/*
	if (!bossManager->GetisBoss1Alive()&& !oneTimeDrop[0])
	{
		vItemManager[0]->SetDropEnemy(BOSSDROP);
		vItemManager[0]->SetDropPos(bossManager->GetBoss1Pos());
		vItemManager[0]->SetIsItem(true);
		oneTimeDrop[0] = true;
	}
	*/
	if (!bossManager->GetisBoss2Alive() && !oneTimeDrop[1])
	{
		vItemManager[1]->SetDropEnemy(BOSSDROP);
		vItemManager[1]->SetIsItem(true);		
		vItemManager[1]->SetDropPos(bossManager->GetBoss2Pos());
		randomItem = rand() % 3;
		vItemManager[1]->SetRandItem(randomItem);
		//randomItem = 1;
		oneTimeDrop[1] = true;
		//vItemManager[1]->SetIsItem(false);
	}
	/*
	if (!bossManager->GetisBoss3Alive() && !oneTimeDrop[2])
	{
		vItemManager[2]->SetDropEnemy(BOSSDROP);
		vItemManager[2]->SetDropPos(bossManager->GetBoss3Pos());
		vItemManager[2]->SetIsItem(true);	
		oneTimeDrop[2] = true;
	}*/
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		//if (isInited)
		//{
		//	TimerManager::GetSingleton()->Update();
		//	this->Update();
		//}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
    //case WM_PAINT:
	//	hdc = BeginPaint(g_hWnd, &ps);
	//	if (isInited)
	//	{
	//		this->Render(hdc);
	//	}
	//	EndPaint(g_hWnd, &ps);
	//	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
