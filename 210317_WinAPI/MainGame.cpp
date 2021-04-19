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

	//이미지를 미리 로드 해두자
	ImageManager::GetSingleton()->AddImage("Enemy","Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("미사일","Image/bullet(2).bmp", 25, 25, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("플레이어 우주선", "Image/playerJet.bmp", 489/2, 131/2, 3, 1, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("구름", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/구슬.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Boss_change", "Image/Boss_change.bmp", 382, 294,1,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));

	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//배경 이미지
	backGround = new Image();
	backGround->Init("Image/Strikers_backGround.bmp", WINSIZE_X, 1360);
	backGroundPos.x = 0;
	backGroundPos.y = -1360 + WINSIZE_Y;
	backCloud = new Image();
	backCloud = ImageManager::GetSingleton()->FindImage("구름");

	//탱크
	tank = new Tank();
	tank->Init();

	// 에너미 메니저
	enemyManager = new EnemyManager();
	enemyManager->Init();

	//플레이어
	playerShip = new PlayerShip();
	playerShip->Init();

	//보스
	bossManager = new BossManager();
	bossManager->Init();

	//초기화 확인
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
	//배경 이동
	backGroundPos.y += 0.05f;

	//탱크(플레이어)
	if (tank)
	{
		tank->Update();
	}

	//적
	if (enemyManager)
	{
		enemyManager->SetPlayerPos(playerShip->GetPos());
		enemyManager->Update();
	}

	//플레이어
	if (playerShip)
	{
		playerShip->Update();
	}

	//플레이어
	if (bossManager)
	{
		bossManager->Update();
	}

	//적 플레이어 충돌 검사
	CheckCollision();

	//InvalidateRect(g_hWnd, NULL, false); //화면갱신
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();

	//배경
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

	// 마우스 좌표

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
	// 적 <-> 탱크 미사일 
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

	// 적 <-> 탱크

	// 적 미사일 <-> 탱크

	// 적 미사일 <-> 탱크 미사일
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
