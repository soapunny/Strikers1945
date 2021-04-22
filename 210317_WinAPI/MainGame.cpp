#include "MainGame.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Image.h"
#include "PlayerShip.h"
#include "BossManager.h"
#include "CollisionCheck.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);
	status = 0;
	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	//�̹����� �̸� �ε� �ص���
	ImageManager::GetSingleton()->AddImage("Enemy","Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
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
	ImageManager::GetSingleton()->AddImage("����", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/����.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("StageTwoBoss", "Image/StageTwoBoss.bmp", 3152*2, 156*2,16,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageThreeBoss", "Image/StageThreeBoss.bmp", 163 * 24, 121, 24, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("������", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y);
	//ImageManager::GetSingleton()->AddImage("����", "Image/ǥ��.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("�� ���", "Image/hitEffect.bmp", 209 * 2, 36 * 2, 6, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("���� ������ ���", "Image/itemExplotion(12).bmp", 1536*2.5, 128*2.5, 12, 1, true, RGB(0, 248, 0));
	
	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//��� �̹���
	backGround = new Image();
	backGround->Init("Image/backGround(3).bmp", WINSIZE_X, 1887);
	backGroundPos.x = 0;
	backGroundPos.y = -1887 + WINSIZE_Y;
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

	//�ʱ�ȭ Ȯ��
	isInited = true;

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

		//�� �÷��̾� �浹 �˻�
		if (collisionCheck)
		{
			collisionCheck->Update();
			CheckCollision();
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
		bossManager->SetBossLife();				//���� ��� ������
		collisionCheck->SetBossCollision(false);
	}
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
