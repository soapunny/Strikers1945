#pragma once
#include "GameNode.h"

class Image;

class CollisionCheck : public GameNode
{
private:
	//플레이어 충돌관련 변수
	RECT RectHit_Player;
	bool playerIsCollision;

	//플레이어 미사일 충돌관련 변수
	RECT RectHit_PlayerMissile;

	//에너미 충돌관련 변수
	RECT RectHit_Enemy;
	bool enemyIsCollision;

	//에너미 미사일 충돌관련 변수
	RECT RectHit_EnemyMissile;

	//교차 영역을 저장할 RECT
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

