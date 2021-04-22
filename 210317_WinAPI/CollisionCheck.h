#pragma once
#include "GameNode.h"

class Image;
class Missile;
class CollisionCheck : public GameNode
{
private:
	int keyCnt;
	Image* hitImg;
	int frameCount;
	int currFrameX; 
	bool hitted;
	FPOINT hitPos;
	float time;

	//
	int playerAttackValue;

	//폭탄 관련 변수
	bool bombUse;
	RECT RectHit_Bomb;

	//플레이어 충돌관련 변수
	RECT RectHit_Player;
	bool playerIsCollision;
	bool isPlayerAlive;

	//플레이어 미사일 충돌관련 변수
	list<Missile*> playerMissile;

	//보스 충돌관련 변수
	RECT RectHit_Boss;
	bool bossIsCollision;
	bool isBossAlive;

	//보스 미사일 충돌관련 변수
	list<Missile*> bossMissile;

	//교차 영역을 저장할 RECT
	RECT rcTemp;

public:
	HRESULT Init();
	void Release();
	void Update();
	void RendEffect(HDC hdc, FPOINT pos);
	void Render(HDC hdc);

	//플레이어
	inline void SetPlayerRect(RECT rect) { this->RectHit_Player = rect; }
	inline void SetPlayerMissile(Missile* missile) { this->playerMissile.push_back(missile); }
	inline void DeletePlayerMissile(Missile* missile) { this->playerMissile.remove(missile); }
	inline void GetPlayerAlive(bool alive) { this->isPlayerAlive = alive; }

	inline bool GetPlayerCollision() { return playerIsCollision; }
	inline void SetPlayerCollision(bool coll) { this->playerIsCollision = coll; }

	//보스
	inline void SetBossRect(RECT rect) { this->RectHit_Boss = rect; }
	inline void SetBossMissile(Missile* missile) { this->bossMissile.push_back(missile); }
	inline void DeleteBossMissile(Missile* missile) { this->bossMissile.remove(missile); }
	inline void GetBossAlive(bool alive) { this->isBossAlive = alive; }

	inline bool GetBossCollision() { return bossIsCollision; }
	inline void SetBossCollision(bool coll) { this->bossIsCollision = coll; }

	//
	inline int GetPlayerAttackValue() { return this->playerAttackValue; }

	//폭탄
	inline void SetBombUse(bool use) { this->bombUse = use; }
	inline void SetBombRect(RECT rect) { this->RectHit_Bomb = rect; }
};

