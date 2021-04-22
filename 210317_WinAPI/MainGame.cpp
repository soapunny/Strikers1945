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
	ImageManager::GetSingleton()->AddImage("�� �̻���", "Image/bullet.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�÷��̾� �̻���","Image/bullet(4).bmp", 20, 20, true, RGB(0, 65, 126));
	ImageManager::GetSingleton()->AddImage("�÷��̾� ���ּ�", "Image/playerJet.bmp", 489/2, 131/2, 3, 1, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("����", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/����.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("StageTwoBoss", "Image/StageTwoBoss.bmp", 3152*2, 156*2,16,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageThreeBoss", "Image/StageThreeBoss.bmp", 163 * 24, 121, 24, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("������", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y);
	ImageManager::GetSingleton()->AddImage("������������", "Image/Life.bmp", 820/10, 793/10,true, RGB(0, 0, 0));
	ImageManager::GetSingleton()->AddImage("��ź������", "Image/bombItem.bmp", 216, 32, 4, 1, true, RGB(0, 128, 128));
	ImageManager::GetSingleton()->AddImage("�Ŀ�������", "Image/powerItem.bmp", 150, 18, 6, 1, true, RGB(0, 128, 128));
	//ImageManager::GetSingleton()->AddImage("����", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255));

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);
	isItemMake[10] = false;
	oneTimeDrop[0] = false;
	oneTimeDrop[1] = false;
	oneTimeDrop[2] = false;
	//��� �̹���
	backGround = new Image();
	backGround->Init("Image/Strikers_backGround(2).bmp", WINSIZE_X, 3604);
	backGroundPos.x = 0;
	backGroundPos.y = -3604 + WINSIZE_Y;
	backCloud = new Image();
	backCloud = ImageManager::GetSingleton()->FindImage("����");
	openingImage = ImageManager::GetSingleton()->FindImage("������");
	endingImage = ImageManager::GetSingleton()->FindImage("����");
	//��ũ
	tank = new Tank();
	tank->Init();

	//�浹
	collisionCheck = new CollisionCheck();
	collisionCheck->Init();

	// ���ʹ� �޴���
	enemyManager = new EnemyManager();
	enemyManager->Init();

	//�÷��̾�
	playerShip = new PlayerShip();
	playerShip->Init(collisionCheck);

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
			backGroundPos.y = -3604 + WINSIZE_Y;
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
			playerShip->Update();
		}

		//�÷��̾�
		if (bossManager)
		{
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
	
	
	
	
	//InvalidateRect(g_hWnd, NULL, false); //ȭ�鰻��
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();
	if (status == 0)//������ ����
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(' '))
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
		if (bossManager)
		{
			bossManager->Render(hBackDC);
		}
	}
	else//���� ���
	{
		if (endingImage)
		{
			endingImage->Render(hBackDC);
		}
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
		//���� ��� ������
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
