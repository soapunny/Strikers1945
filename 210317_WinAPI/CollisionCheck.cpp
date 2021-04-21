#include "CollisionCheck.h"
#include "CommonFunction.h"
#include "PlayerShip.h"
#include "MissileManager.h"
#include "Missile.h"

HRESULT CollisionCheck::Init()
{
	playerIsCollision = false;
	bossIsCollision = false;

	//playerMissile = new list<Missile*>();

	return S_OK;
}

void CollisionCheck::Release()
{
}

void CollisionCheck::Update()
{
	list<Missile*>::iterator myIt;
	
	//"플레이어"와 "보스 미사일" 충돌
	for (myIt = bossMissile.begin(); myIt != bossMissile.end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == true)
		{
			if (IntersectRect(&rcTemp, &RectHit_Player, (*myIt)->GetPlayerMissileRect()))
			{
				playerIsCollision = true;
			}
		}
	}

	//"플레이어 미사일"과 "보스"충돌
	for (myIt = playerMissile.begin(); myIt != playerMissile.end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == true)
		{
			if (IntersectRect(&rcTemp, &RectHit_Boss, (*myIt)->GetPlayerMissileRect()))
			{
				bossIsCollision = true;
				(*myIt)->SetIsFired(false);
				this->playerMissile.remove((*myIt));
			}
		}
	}
	
	
}

void CollisionCheck::Render(HDC hdc)
{
	//플레이어 충돌 박스
	RenderRectToCenter(hdc, RectHit_Player.left, RectHit_Player.top, RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);

	//보스 충돌 박스
	RenderRectToCenter(hdc, RectHit_Boss.left, RectHit_Boss.top, RectHit_Boss.right - RectHit_Boss.left, RectHit_Boss.bottom - RectHit_Boss.top);

	//플레리어 미사일 충돌 박스
	list<Missile*>::iterator myIt;
	for (myIt = playerMissile.begin(); myIt != playerMissile.end(); myIt++)
	{
		if ((*myIt)->GetIsFired() == true)
		{
			RenderRectToCenter(hdc, (*myIt)->GetPlayerMissileRect()->left, (*myIt)->GetPlayerMissileRect()->top,
				(*myIt)->GetPlayerMissileRect()->right - (*myIt)->GetPlayerMissileRect()->left,
				(*myIt)->GetPlayerMissileRect()->bottom - (*myIt)->GetPlayerMissileRect()->top);
		}
	}
}
