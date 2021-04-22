#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init()
{
	return E_FAIL;
}

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;

	playerPower = 1;
	attackValue = 1;
	
	image = ImageManager::GetSingleton()->FindImage("플레이어 우주선");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}
	currFrameX = 1;

	explosionImage = ImageManager::GetSingleton()->FindImage("폭발 아이템 사용");
	if (explosionImage == nullptr)
	{
		MessageBox(g_hWnd, "폭발 아이템 사용 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}
	currFrameX_ex = 0;
	imageTime = 0;
	bombUse = false;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 50;

	moveSpeed = 300.0f;

	isAlive = true;
	isDying = false;
	canMove = false;

	playerLife = 100;

	collisionSize.x = 35;
	collisionSize.y = 50;

	//playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	//collisionCheck->SetPlayerRect(playerRect);

	//포신
	barrelSize = 1;
	
	barrelEnd[0] = { (pos.x - 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[1] = { (pos.x + 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[2] = { (pos.x + cosf(barrelAngle[2]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[3] = { (pos.x + cosf(barrelAngle[3]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[4] = { (pos.x) ,  pos.y - barrelSize * 2 };

	barrelAngle[0] = PI / 2;
	barrelAngle[1] = PI / 2;
	barrelAngle[2] = 3 * (PI / 4);
	barrelAngle[3] = PI / 4;
	barrelAngle[4] = PI / 2;

	barrelAlive[0] = false;
	barrelAlive[1] = false;
	barrelAlive[2] = false;
	barrelAlive[3] = false;
	barrelAlive[4] = true;

	//미사일
	for (int i = 0; i < 5; i++)
	{
		myMissile[i] = new MissileManager();
		if (barrelAlive[i])
			myMissile[i]->Init(this->collisionCheck, barrelEnd[i]);
		else
			myMissile[i]->Init(this->collisionCheck, {-100, -100});
	}
	fireCount = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < 5; i++)
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
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	//충돌
	//playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	playerRect = { (LONG)(pos.x - collisionSize.x / 3), (LONG)(pos.y - collisionSize.y / 3), (LONG)(pos.x + collisionSize.x / 3), (LONG)(pos.y + collisionSize.y / 3) };
	collisionCheck->SetPlayerRect(playerRect);

	//첫 등장 (아래에서 위로)
	if (!canMove)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= elapsedTime * 500.0f;// 1.0f;
		else
			canMove = true;
	}

	//알파블랜드
	if (isAlive && KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		isAlive = false;
		isDying = true;
	}

	//이동
	if (isDying)
	{
		OnDead();
	}
	else if(!isDying && canMove)
	{
		Move();
	}

	// 포신 위치, 각도에 따른 좌표 계산
	for (int i = 0; i < 2; i++)
	{
		barrelEnd[i] = { (pos.x - 10.0f + (20.0f * i)), (pos.y - barrelSize) };
	}

	for (int i = 2; i < 4; i++)
	{
		barrelEnd[i] = { ((pos.x - 10.0f + (20.0f * (i - 2))) + cosf(barrelAngle[i])* barrelSize) , pos.y - barrelSize };
	}

	for (int i = 4; i < 5; i++)
	{
		barrelEnd[i] = { (pos.x), (pos.y - barrelSize) };
	}

	for (int i = 0; i < 5; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->SetOwnerType(MissileManager::OWNERTYPE::Player);
			myMissile[i]->SetPlayerPos(this->pos); 
			if (barrelAlive[i])
				myMissile[i]->SetPos(barrelEnd[i]);
			myMissile[i]->SetAngle(barrelAngle[i]);
			myMissile[i]->SetPlayerPower(this->playerPower);
			myMissile[i]->Update();
			//공격
			Attack(i);
		}
	}
}

void PlayerShip::Render(HDC hdc)
{
	//파워 표시
	wsprintf(szText, "Player Power: %d", playerPower);
	TextOut(hdc, WINSIZE_X - 150, 160, szText, strlen(szText));

	//파워 표시
	wsprintf(szText, "Attack Value: %d", attackValue);
	TextOut(hdc, WINSIZE_X - 150, 180, szText, strlen(szText));

	//life 표시
	wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));

	//이미지
	if (image)
	{
		if(!isAlive)
			image->AlphaRender(hdc, pos.x, pos.y, true);
		if(isAlive)
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
	}

	// 포신
	if (playerPower == 1)
	{
		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd[4].x, barrelEnd[4].y);
	}
	if (playerPower >= 2)
	{
		barrelAlive[4] = false;
		barrelEnd[4] = { -100, -100 };

		barrelAlive[0] = true;
		barrelAlive[1] = true;

		MoveToEx(hdc, pos.x - 10, pos.y, NULL);
		LineTo(hdc, barrelEnd[0].x, barrelEnd[0].y);

		MoveToEx(hdc, pos.x + 10, pos.y, NULL);
		LineTo(hdc, barrelEnd[1].x, barrelEnd[1].y);

		if (playerPower >= 3)
		{
			barrelAlive[2] = true;
			barrelAlive[3] = true;

			MoveToEx(hdc, pos.x - 10, pos.y, NULL);
			LineTo(hdc, barrelEnd[2].x, barrelEnd[2].y);

			MoveToEx(hdc, pos.x + 10, pos.y, NULL);
			LineTo(hdc, barrelEnd[3].x, barrelEnd[3].y);
		}

	}

	//미사일
	for (int i = 0; i < 5; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}

	//폭발 아이템 사용/////////////////////////////////////
	if (KeyManager::GetSingleton()->IsOnceKeyDown('E'))
	{
		exPos = pos;
		tempSize = 0;
		bombUse = true;
	}
	if (bombUse)
	{
		if (currFrameX_ex < 5)
			tempSize = 30 * currFrameX_ex;
		else
			tempSize = 150;

		bombRect = { (LONG)(exPos.x - tempSize), (LONG)((exPos.y - 150) - tempSize),
		(LONG)(exPos.x + tempSize), (LONG)((exPos.y - 150) + tempSize) };
		collisionCheck->SetBombRect(bombRect);

		explosionImage->FrameRender(hdc, exPos.x, exPos.y - 150, currFrameX_ex, 0, true);

		imageTime += TimerManager::GetSingleton()->getElapsedTime();
		if (imageTime > 0.1f)
		{
			if (currFrameX_ex < 12)
				currFrameX_ex++;
			else
			{
				currFrameX_ex = 0;
				bombUse = false;
				//
			}
			imageTime = 0;
		}
	}

	(this->collisionCheck)->SetBombUse(this->bombUse);
}

void PlayerShip::Move()
{
	currFrameX = 1;
	collisionSize.x = 35;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		collisionSize.x = 22;
		currFrameX = 0;
		if(pos.x > 20)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		collisionSize.x = 22;
		currFrameX = 2;
		if (pos.x < WINSIZE_X - 20)
			pos.x += moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		if (pos.y > 30)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		if (pos.y < WINSIZE_Y - 30)
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
		if (fireCount % 50 == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if(barrelAlive[i])
					myMissile[i]->Fire(FIRETYPE::PlayerFIRE);
			}
			fireCount = 0;
		}
	}
}
