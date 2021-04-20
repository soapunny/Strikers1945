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

	//이미지를 미리 로드 해두자
	ImageManager::GetSingleton()->AddImage("Enemy","Image/ufo.bmp", 530, 32, 10, 1, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("미사일","Image/bullet(4).bmp", 20, 20, true, RGB(0, 65, 126));
	ImageManager::GetSingleton()->AddImage("플레이어 우주선", "Image/playerJet.bmp", 489/2, 131/2, 3, 1, true, RGB(248, 0, 248));
	ImageManager::GetSingleton()->AddImage("구름", "Image/cloud.bmp", WINSIZE_X, 1360, true, RGB(246, 246, 246));
	ImageManager::GetSingleton()->AddImage("EnemyMissile","Image/구슬.bmp", 20, 20, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Boss_change", "Image/Boss_change.bmp", 382, 294,1,1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageOneBoss", "Image/StageOneBoss.bmp", 186*30, 186, 30, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("StageThreeBoss", "Image/StageThreeBoss.bmp", 163 * 24, 121, 24, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("오프닝", "Image/표지.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255));
	ImageManager::GetSingleton()->AddImage("엔딩", "Image/표지.bmp", WINSIZE_X, WINSIZE_Y, 1, 1, true, RGB(255, 255, 255));

	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	//배경 이미지
	backGround = new Image();
	backGround->Init("Image/Strikers_backGround.bmp", WINSIZE_X, 2694);
	//backGround->Init("Image/Strikers_backGround(2).bmp", WINSIZE_X, 3604);
	backGroundPos.x = 0;
	backGroundPos.y = -2694 + WINSIZE_Y;
	backCloud = new Image();
	backCloud = ImageManager::GetSingleton()->FindImage("구름");

	openingImage = new Image();
	openingImage = ImageManager::GetSingleton()->FindImage("오프닝");

	endingImage = new Image();
	endingImage = ImageManager::GetSingleton()->FindImage("엔딩");
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

	//충돌
	collisionCheck = new CollisionCheck();
	collisionCheck->Init();

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
	SAFE_RELEASE(collisionCheck);

	SAFE_RELEASE(openingImage); 
	SAFE_RELEASE(endingImage);
	
	ReleaseDC(g_hWnd, hdc);

	//KillTimer(g_hWnd, 0);
}

void MainGame::Update()
{
	//배경 이동
	if (status >= 1)
	{
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
		if (collisionCheck)
		{
			collisionCheck->SetPlayerRect(playerShip->GetPlayerRect());
			collisionCheck->Update();
			CheckCollision();
		}
	}
	


	//InvalidateRect(g_hWnd, NULL, false); //화면갱신
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();
	if (status == 0)//오프닝 상태
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(' '))
		{
			status++;
			//sceneManagerObserver->OpeningNotify(status);
			//오프닝 넘기기
		}
		if (openingImage)
		{
			openingImage->Render(hBackDC);
		}
	}
	else if (status == 1)
	{
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
	else//엔딩 출력
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
	//플레이어와 에너미 미사일이 출동했다면
	if (collisionCheck->GetPlayerCollision())
	{
		playerShip->SetPlayerLife();				//플레이어 목숨 하나 줄이기
		collisionCheck->SetPlayerCollision(false);
	}

	//플레이어 미사일과 에너미 미사일이 출동했다면
	if (collisionCheck->GetEnemyCollision())
	{
		//에너미 목숨 줄이자
		collisionCheck->SetEnemyCollision(false);
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
