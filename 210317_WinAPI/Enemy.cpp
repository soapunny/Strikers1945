#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"
#include "CollisionCheck.h"
HRESULT Enemy::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
	this->collisionCheck = collisionCheck;

	//ufo
	image = ImageManager::GetSingleton()->FindImage("Enemy");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
		return E_FAIL;
	}
	currFrameX = 0;
	updateCount = 0;

	fireType = FIRETYPE::NormalFIRE;

	pos.x = posX;
	pos.y = posY;
	size = 80;
	name = "NormalEnemy";
	shape = { 0, 0, 0, 0 };
	moveSpeed = 100.0f;
	isAlive = true;
	angle = -PI / 2.0f;
	target = nullptr;
	dir = 1;

	// 미사일
	//myMissile = new MissileManager();
	//myMissile->Init(pos);
	fireTimer1 = 0.0f;
	fireTimer2 = 0.0f;
	fireCount2 = 0;

	return S_OK;
}

void Enemy::Release()
{
	if (myMissile)
	{
		myMissile->Release();
		delete myMissile;
		myMissile = nullptr;
	}

}

void Enemy::Attack()
{
	if (myMissile)
	{
		//myMissile->Update();

		fireTimer1 += TimerManager::GetSingleton()->getElapsedTime();
		if ((int)fireTimer1 / 2 == 1)
		{
			//FPOINT barrelPos = { pos.x, pos.y + size};
			//myMissile->SetPos(barrelPos);
			myMissile->Fire(fireType);
			fireTimer1 = 0.0f;
		}
	}
}

void Enemy::Update()
{
	if (isAlive)
	{
		if (myMissile)
		{
			fireTimer2 += TimerManager::GetSingleton()->getElapsedTime();
			if ((int)fireTimer2 / 1 == 1)
			{
				//myMissile->SetPlayerPos(pos);
				myMissile->SetOwnerType(MissileManager::OWNERTYPE::Enemy);
				myMissile->SetAngle(DegToRad(-90));

				fireTimer2 = 0.0f;
			}
			FPOINT barrelPos = { pos.x, pos.y + size/2 };
			myMissile->SetPos(barrelPos);
			myMissile->Update();
		}

		//애니메이션
		updateCount++;
		if (updateCount >= 5)
		{
			//currFrameX = (currFrameX + 1) % 10;
			updateCount = 0;
		}
		Move();
	}
}

void Enemy::Render(HDC hdc)
{
	if (isAlive)
	{
		//RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

		if (image)
		{
			image->Render(hdc, size, pos.x, pos.y, true);
		}

		//미사일
		if (myMissile)
		{
			myMissile->Render(hdc);
		}
	}
}

void Enemy::Move()
{
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	pos.x += cosf(angle) * moveSpeed * elapsedTime;
	pos.y -= sinf(angle) * moveSpeed * elapsedTime;
}

void Enemy::HorizonMove()
{
	if (pos.x > WINSIZE_X || pos.x < 0)
	{
		dir *= -1;
	}
	pos.x += moveSpeed * dir;
}
