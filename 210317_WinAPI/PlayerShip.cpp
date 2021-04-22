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
	
	explosionimage = ImageManager::GetSingleton()->FindImage("보스폭발");
	blinkImage = ImageManager::GetSingleton()->FindImage("플레이어 깜빡임 우주선");
	image = ImageManager::GetSingleton()->FindImage("플레이어 우주선");
	retryImage = ImageManager::GetSingleton()->FindImage("패배엔딩");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "플레이어 우주선 이미지 로드 실패", "실패", MB_OK);
		return E_FAIL;
	}
	currFrameX = 1;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 50;

	moveSpeed = 300.0f;

	isAlive = true;
	isDying = false;
	canMove = false;
	reAppear = false;
	playerLife = 5;

	collisionSize.x = 35;
	collisionSize.y = 50;

	explosionCurrFrame = 0;
	blinkCount = 0;
	explosionCount=0;
	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	collisionCheck->SetPlayerRect(playerRect);

	//포신
	barrelSize = 1;
	barrelEnd[0] = { (pos.x - 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[1] = { (pos.x + 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[2] = { (pos.x + cosf(barrelAngle[2]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[3] = { (pos.x + cosf(barrelAngle[3]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelAngle[0] = PI / 2;
	barrelAngle[1] = PI / 2;
	barrelAngle[2] = 3 * (PI / 4);
	barrelAngle[3] = PI / 4;

	//미사일
	for (int i = 0; i < 4; i++)
	{
		myMissile[i] = new MissileManager();
		myMissile[i]->Init(this->collisionCheck, barrelEnd[i]);
	}
	fireCount = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < 4; i++)
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

	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	collisionCheck->SetPlayerRect(playerRect);

	//첫 등장 (아래에서 위로)
	if (!canMove)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= elapsedTime * 500.0f;// 1.0f;
		else
			canMove = true;
	}

	if (playerLife <= 0)
	{
		isAlive = false;
	}

	//알파블랜드
	if (isAlive && KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))//죽고 등장하면 깜빡거림
	{
		isAlive = false;
		isDying = true;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('H'))//충돌처리 플레이어 죽으면 터지면서 다시등장
	{
		
	//	pos.x = WINSIZE_X / 2;
		//pos.y = WINSIZE_Y + 50;
		canMove = false;
		lifeDecrease = true;
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

	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->SetOwnerType(MissileManager::OWNERTYPE::Player);
			myMissile[i]->SetPlayerPos(this->pos);
			myMissile[i]->SetPos(barrelEnd[i]);
			myMissile[i]->SetAngle(barrelAngle[i]);
			myMissile[i]->Update();
			//공격
			Attack(i);
		}
	}
	if (!isAlive)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('R')) //죽엇을때 다시시작할건지 묻기 R을 누르면 진행되던 스테이지에서 그대로 시작
		{
			playerLife = 5;
			isAlive = true;
		}
	}
}

void PlayerShip::Render(HDC hdc)
{
	//life 표시
	wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));

	//이미지
	if (image)
	{
		if (reAppear == true)//깜박이며 다시등장하기 AlphaRender는 프레임이 없어서 좀 고쳐야할듯
		{
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

			if (blinkCount > 175)
			{
				blinkCount = 0;
				reAppear = false;
			}

		}
		else
		{

			if (isAlive)
			{
				image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
			}
			else //죽으면 다시도전할수 있는 화면 띄우기
			{
				retryImage->Render(hdc);

			}
		}
			//image->AlphaRender(hdc, pos.x, pos.y, true);
	}



	if (lifeDecrease == true )//폭발이미지 출력부분
	{	
		explosionCount++;
		if (explosionCount > 3)
		{
			explosionCurrFrame++; 
			explosionCount = 0;
		}
		
		explosionimage->FrameRender(hdc,pos.x, pos.y , explosionCurrFrame, 0, true);
		//explosionimage->FrameRender(hdc, pos.x, pos.y + 80, explosionCurrFrame, 0, true);
		if (explosionCurrFrame > 10)
		{
			canMove = false;
			pos.x = WINSIZE_X / 2;
			pos.y = WINSIZE_Y + 50;
		}
		if (explosionCurrFrame > 16)
		{
			explosionCurrFrame = 0;
			lifeDecrease = false;
			playerLife -= 1;
			reAppear = true;
			
			
		}
	}

	// 포신
	MoveToEx(hdc, pos.x-10, pos.y, NULL);
	LineTo(hdc, barrelEnd[0].x, barrelEnd[0].y);

	MoveToEx(hdc, pos.x+10, pos.y, NULL);
	LineTo(hdc, barrelEnd[1].x, barrelEnd[1].y);

	MoveToEx(hdc, pos.x - 10, pos.y, NULL);
	LineTo(hdc, barrelEnd[2].x, barrelEnd[2].y);

	MoveToEx(hdc, pos.x + 10, pos.y, NULL);
	LineTo(hdc, barrelEnd[3].x, barrelEnd[3].y);

	//미사일
	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}
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
		if (fireCount % 100 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				myMissile[i]->Fire(FIRETYPE::PlayerFIRE);
			}
			fireCount = 0;
		}
	}
}
