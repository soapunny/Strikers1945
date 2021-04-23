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
	
	blinkImage = ImageManager::GetSingleton()->FindImage("플레이어 깜빡임 우주선");
	retryImage = ImageManager::GetSingleton()->FindImage("패배엔딩");
	playerExplosion = ImageManager::GetSingleton()->FindImage("보스폭발");
	playerExplosionStart = false;
	explosionCurrFrame = 0;
	explosionTime = 0.0f;
	blinkCount = 0;
	reAppear = false;
	
	//플레이어
	image = ImageManager::GetSingleton()->FindImage("플레이어 우주선");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}
	currFrameX = 1;

	//폭발
	explosionImage = ImageManager::GetSingleton()->FindImage("폭발 아이템 사용");
	if (explosionImage == nullptr)
	{
		MessageBox(g_hWnd, "폭발 아이템 사용 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}
	currFrameX_ex = 0;
	imageTime = 0;
	bombUse = false;
	
	//생명
	for (int i = 0; i < 5; i++)
	{
		lifeImg[i] = ImageManager::GetSingleton()->FindImage("라이프띄어주기");
	}
	playerLife = 5;

	//폭탄
	for (int i = 0; i < 3; i++)
	{
		bombImg[i] = ImageManager::GetSingleton()->FindImage("폭탄띄어주기");
	}
	bombNum = 3;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 50;

	moveSpeed = 300.0f;

	isAlive = true;
	//isDying = false;
	canMove = false;

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
	fireTime = 0;

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
	playerRect = { (LONG)(pos.x - collisionSize.x / 3), (LONG)(pos.y - collisionSize.y / 3), (LONG)(pos.x + collisionSize.x / 3), (LONG)(pos.y + collisionSize.y / 3) };
	collisionCheck->SetPlayerRect(playerRect);

	//첫 등장 (아래에서 위로)
	if (!canMove && reAppear == false && playerExplosionStart == false)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= elapsedTime * 250.0f;// 1.0f;
		else
			canMove = true;
	}
	else if(canMove && reAppear == false)
	{
		Move();
	}

	//플레이어 죽으면
	if (playerLife == 0)
	{
		//폭발이미지 출력
		canMove = false;
		playerExplosionStart = true;
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

	//죽엇을때 다시시작할건지 묻기 R을 누르면 진행되던 스테이지에서 그대로 시작
	if (!isAlive)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('Y'))
		{
			pos.x = WINSIZE_X / 2;
			pos.y = WINSIZE_Y + 50;
			playerLife = 5;
			isAlive = true;
			reAppear = true;			//깜빡이면서 올라오기 시작  
		}
	}

	//플레이어 life 최대 5
	//if (playerLife >= 5)
	//{
	//	playerLife = 5;
	//}

	////폭탄 개수 최대 3
	//if (bombNum >= 3)
	//{
	//	bombNum = 3;
	//}

	if (bombNum >= 1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
		{
			bombNum -= 1;
			exPos = pos;
			tempSize = 0;
			bombUse = true;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		if (playerPower < 3)
			playerPower += 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		if (playerLife < 5)
			playerLife += 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
	{
		if (bombNum < 3)
			bombNum += 1;
	}
}

void PlayerShip::Render(HDC hdc)
{
	//life 그려주기
	if (playerLife >= 0)
	{
		for (int i = 0; i < playerLife; i++)
		{
			lifeImg[i]->Render(hdc, 30 + 45 * i, 40, true);
		}
	}
	//bomb 그려주기
	for (int i = 0; i < bombNum; i++)
	{
		bombImg[i]->Render(hdc, 30 + 45 * i, WINSIZE_Y - 40, true);
	}
	/*wsprintf(szText, "bomb: %d", bombNum);
	TextOut(hdc, WINSIZE_X - 150, 200, szText, strlen(szText));*/

	//파워 표시
	wsprintf(szText, "Player Power: %d", playerPower);
	TextOut(hdc, WINSIZE_X - 150, 160, szText, strlen(szText));

	//파워 표시
	wsprintf(szText, "Attack Value: %d", attackValue);
	TextOut(hdc, WINSIZE_X - 150, 180, szText, strlen(szText));

	//life 표시
	/*wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));*/

	//이미지
	if (image)
	{
		if (isAlive && reAppear == false)
		{
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
		}
		else //죽으면 다시도전할수 있는 화면 띄우기
		{
			playerExplosionStart = false;
			//retryImage->Render(hdc);
		}
		//image->AlphaRender(hdc, pos.x, pos.y, true);
	}

	//폭발이미지 출력부분
	if (playerExplosionStart && reAppear == false)
	{
		playerExplosion->FrameRender(hdc, pos.x, pos.y, explosionCurrFrame, 0, true);

		explosionTime += 1.0f;
		if (explosionTime > 5.0f)
		{
			explosionCurrFrame++;
			explosionTime = 0.0f;
		}

		if (explosionCurrFrame >= 16)	//폭발 이미지 끝남
		{
			explosionCurrFrame = 0;
			explosionTime = 0.0f;
			isAlive = false;			//엔딩씬
			playerExplosionStart = false;
		}
	}

	//깜박이며 다시등장하기 AlphaRender는 프레임이 없어서 좀 고쳐야할듯
	if (reAppear == true)
	{
		playerLife = 5;

		blinkImage->AlphaRender(hdc, pos.x, pos.y, true);//AlphaRender 고쳐되 괜찮은지 묻기

		BLENDFUNCTION* blendFunc = blinkImage->GetBlendFunc();//하나짜리 프레임의 비행기 이미지띄우는걸로 결정 ㅎㅎ
		blinkCount++;
		if (blinkCount % 2 == 0)
		{
			blendFunc->SourceConstantAlpha = 0;
		}
		else
		{
			blendFunc->SourceConstantAlpha = 255;
		}

		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= TimerManager::GetSingleton()->getElapsedTime() * 250.0f;// 1.0f;

		else
		{
			blinkCount = 0;
			reAppear = false;
			canMove = true;
		}
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
	if (canMove)
	{
		currFrameX = 1;
		collisionSize.x = 35;

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			collisionSize.x = 22;
			currFrameX = 0;
			if (pos.x > 20)
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
}

void PlayerShip::Attack(int i)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z') && canMove)
	{
		fireTime += TimerManager::GetSingleton()->getElapsedTime();
		if (fireTime > 0.5f)
		{
			for (int i = 0; i < 5; i++)
			{
				if(barrelAlive[i])
					myMissile[i]->Fire(FIRETYPE::PlayerFIRE);
			}
			fireTime = 0;
		}
	}
}
