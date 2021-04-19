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
	//�÷��̾�� ���ʹ� �̻��� �浹
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		//if (IntersectRect(&rcTemp, &RectHit_Player, &RectHit_EnemyMissile))
		{
			playerIsCollision = true;
		}
	}

	//�÷��̾� �̻��ϰ� ���ʹ��浹
	if (IntersectRect(&rcTemp, &RectHit_Enemy, &RectHit_PlayerMissile))
	{
		enemyIsCollision = true;
	}
}

void CollisionCheck::Render(HDC hdc)
{
	//�÷��̾� �浹 �ڽ�
	RenderRectToCenter(hdc, RectHit_Player.left, RectHit_Player.top, RectHit_Player.right - RectHit_Player.left, RectHit_Player.bottom - RectHit_Player.top);
}
