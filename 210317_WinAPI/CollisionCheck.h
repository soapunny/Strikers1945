#pragma once
#include "GameNode.h"

class Image;

class CollisionCheck : public GameNode
{
private:
	//�÷��̾� �浹���� ����
	RECT RectHit_Player;
	bool playerIsCollision;

	//�÷��̾� �̻��� �浹���� ����
	RECT RectHit_PlayerMissile;

	//���ʹ� �浹���� ����
	RECT RectHit_Enemy;
	bool enemyIsCollision;

	//���ʹ� �̻��� �浹���� ����
	RECT RectHit_EnemyMissile;

	//���� ������ ������ RECT
	RECT rcTemp;			

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetPlayerRect(RECT rect) { this->RectHit_Player = rect; }
	inline void SetPlayerMissileRect(RECT rect) { this->RectHit_PlayerMissile = rect; }
	inline void SetEnemyRect(RECT rect) { this->RectHit_Enemy = rect; }
	inline void SetEnemyMissileRect(RECT rect) { this->RectHit_EnemyMissile = rect; }

	inline bool GetPlayerCollision() { return playerIsCollision; }
	inline void SetPlayerCollision(bool coll) { this->playerIsCollision = coll; }
	inline bool GetEnemyCollision() { return enemyIsCollision; }
	inline void SetEnemyCollision(bool coll) { this->enemyIsCollision = coll; }
};

