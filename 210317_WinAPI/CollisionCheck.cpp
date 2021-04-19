#include "CollisionCheck.h"
#include "CommonFunction.h"
#include "PlayerShip.h"

HRESULT CollisionCheck::Init()
{
	playerIsCollision = false;
	enemyIsCollision = false;

	return S_OK;
}

void CollisionCheck::Release()
{
}

void CollisionCheck::Update()
{
	//플레이어와 에너미 미사일 충돌
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		//if (IntersectRect(&rcTemp, &RectHit_Player, &RectHit_EnemyMissile))
		{
			playerIsCollision = true;
		}
	}

	//플레이어 미사일과 에너미충돌
	if (IntersectRect(&rcTemp, &RectHit_Enemy, &RectHit_PlayerMissile))
	{
		enemyIsCollision = true;
	}
}

void CollisionCheck::Render(HDC hdc)
{
	//플레이어 충돌 박스
	RenderRectToCenter(hdc, RectHit_Player.left, RectHit_Player.top, RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);
}
