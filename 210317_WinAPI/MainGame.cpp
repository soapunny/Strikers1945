#include "MainGame.h"
#include "Tank.h"
#include "EnemyManager.h"
#include "Image.h"
#include "PlayerShip.h"
#include "BossManager.h"

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	//�̹����� �̸� �ε� �ص���
	ImageManager::GetSingleton()->AddImage("Enemy","Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("�̻���","Image/bullet(2).bmp", 25, 25, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("�÷��̾� ���ּ�", "Image/playerJet.bmp", 489/2, 131/2, 3, 1, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("����", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/����.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Boss_change", "Image/Boss_change.bmp", 382, 294,1,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));

	// ���ΰ����� �ʱ�ȭ �Լ�
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// ����� �̹���
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//��� �̹���
	backGround = new Image();
	backGround->Init("Image/Strikers_backGround.bmp", WINSIZE_X, 1360);
	backGroundPos.x = 0;
	backGroundPos.y = -1360 + WINSIZE_Y;
	backCloud = new Image();
	backCloud = ImageManager::GetSingleton()->FindImage("����");

	//��ũ
	tank = new Tank();
	tank->Init();

	// ���ʹ� �޴���
	enemyManager = new EnemyManager();
	enemyManager->Init();

	//�÷��̾�
	playerShip = new PlayerShip();
	playerShip->Init();

	//����
	bossManager = new BossManager();
	bossManager->Init();

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

	ReleaseDC(g_hWnd, hdc);

	//KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	//��� �̵�
	backGroundPos.y += 0.05f;

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
	CheckCollision();

	//InvalidateRect(g_hWnd, NULL, false); //ȭ�鰻��
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

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

	// ���콺 ��ǥ

	//FPS
	TimerManager::GetSingleton()->Render(hBackDC);

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

	backBuffer->Render(hdc);
}

void MainGame::CheckCollision()
{
	/*
	// �� <-> ��ũ �̻��� 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;

	for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i].GetIsAlive() == false)	continue;

		for (int j = 0; j < tank->GetMissileCount(); j++)
		{
			if (missileArray[j].GetIsFired() == false)	continue;

			enemyPos = enemy[i].GetPos();
			missilePos = missileArray[j].GetPos();

			x = enemyPos.x - missilePos.x;
			y = enemyPos.y - missilePos.y;

			distance = sqrtf(x * x + y * y);

			r1 = enemy[i].GetSize() / 2;
			r2 = missileArray[j].GetSize() / 2;

			if (distance <= r1 + r2)
			{
				enemy[i].SetIsAlive(false);
				missileArray[j].SetIsFired(false);
				break;
			}
		}
	}

	// �� <-> ��ũ

	// �� �̻��� <-> ��ũ

	// �� �̻��� <-> ��ũ �̻���
	*/
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
