#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->AddImage("플레이어 우주선", "Image/rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y - 150;

	moveSpeed = 150.0f;

	isAlive = true;
	isDying = false;

	// 테스트 용 포신 //
	barrelSize = 100;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelEnd2.x = pos.x;
	barrelEnd2.y = pos.y - barrelSize;
	barrelEnd3.x = pos.x;
	barrelEnd3.y = pos.y - barrelSize;
	barrelAngle = 2* 3.14f / 4.0f;
	barrelAngle2 = 2 * 3.14f / 4.0f;
	barrelAngle3 = 2 * 3.14f / 4.0f;

	// 테스트 용 포신 미사일//
	myMissile[0] = new MissileManager();
	myMissile[0]->Init(barrelEnd);
	myMissile[1] = new MissileManager();
	myMissile[1]->Init(barrelEnd2);
	myMissile[2] = new MissileManager();
	myMissile[2]->Init(barrelEnd3);
	fireCount = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < 3; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Release();
			delete myMissile[i];
			myMissile[i] = nullptr;
		}
	}
}

void PlayerShip::Update()
{
	if (isAlive && KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		isAlive = false;
		isDying = true;
	}

	if (isDying)
	{
		OnDead();
	}
	else
	{
		Move();
	}

	//
	RotateBarrel(3.14f / 4.0f);
	
	// 포신 각도에 따른 좌표 계산
	barrelEnd.x = pos.x + cosf(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - (sinf(barrelAngle) * barrelSize);

	barrelEnd2.x = pos.x + cosf(barrelAngle2) * barrelSize - 10;
	barrelEnd2.y = pos.y - (sinf(barrelAngle2) * barrelSize);

	barrelEnd3.x = pos.x + cosf(barrelAngle3) * barrelSize + 10;
	barrelEnd3.y = pos.y - (sinf(barrelAngle3) * barrelSize);


	myMissile[0]->SetPos(barrelEnd);
	myMissile[1]->SetPos(barrelEnd2);
	myMissile[2]->SetPos(barrelEnd3);
	for (int i = 0; i < 3; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Update();
			//공격
			Attack(i);
		}
	}
}

void PlayerShip::Render(HDC hdc)
{
	if (image)
	{
		if(!isAlive)
			image->AlphaRender(hdc, pos.x, pos.y, true);
		if(isAlive)
			image->Render(hdc, pos.x, pos.y, true);
	}

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	MoveToEx(hdc, pos.x-10, pos.y, NULL);
	LineTo(hdc, barrelEnd2.x, barrelEnd2.y);

	MoveToEx(hdc, pos.x+10, pos.y, NULL);
	LineTo(hdc, barrelEnd3.x, barrelEnd3.y);

	//미사일
	for (int i = 0; i < 3; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}
}

void PlayerShip::RotateBarrel(float angle)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		barrelAngle2 = 0;
		barrelAngle3 = 4 * angle;
	}
}

void PlayerShip::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		pos.x -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		pos.x += moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		pos.y -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		pos.y += moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
}

void PlayerShip::OnDead()
{
	if (image)
	{
		BLENDFUNCTION* blendFunc = image->GetBlendFunc();
		if (blendFunc->SourceConstantAlpha > 0)
		{
			blendFunc->SourceConstantAlpha--;
		}
		else
		{
			isDying = false;
			isAlive = false;
		}
	}
}

void PlayerShip::Attack(int i)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		fireCount++;
		if (fireCount % 20 == 0)
		{
			myMissile[i]->Fire(MissileManager::FIRETYPE::NormalFIRE);
			fireCount = 0;
		}
	}
}
