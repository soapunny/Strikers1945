#pragma once
#include "GameNode.h"

class Image;
class Missile;
class Enemy;
class Item;
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

	//아이템 1번 power, 2번 bomb, 3번 life
	int item;
	RECT RectHit_item;
	bool bombIsCollision;
	bool powerIsCollision;
	bool lifeIsCollision;
	list<Item*> itemData;

	//플레이어 폭탄 관련 변수
	bool bombUse;
	RECT RectHit_Bomb;

	//플레이어 충돌관련 변수
	RECT RectHit_Player;
	bool playerIsCollision;
	bool isPlayerAlive;

	//플레이어 미사일 충돌관련 변수
	list<Missile*> playerMissile;
	
	//잡몹 충돌
	list<Enemy*> enemyData;
	bool enemyIsCollision;
	bool isEnemyAlive;

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

	//잡몹
	inline void SetEnemy(Enemy* enemy) { this->enemyData.push_back(enemy); }
	
	inline bool GetEnemyCollision() { return enemyIsCollision; }
	inline void SetEnemyCollision(bool coll) { this->enemyIsCollision = coll; }
	inline void DeleteEnemy(Enemy* enemy) { this->enemyData.remove(enemy); }
	void DeleteEnemyMissile(Missile* missile);
	inline void GetEnemyAlive(bool alive) { this->isEnemyAlive = alive; }

	//폭탄
	inline void SetBombUse(bool use) { this->bombUse = use; }
	inline void SetBombRect(RECT rect) { this->RectHit_Bomb = rect; }

	//아이템
	inline void SetItem(Item* item) { this->itemData.push_back(item); }
	inline void SetItem(int num) { this->item = num; }

	inline int GetPowerCollision() { return this->powerIsCollision; }
	inline void SetPowerCollision(bool coll) { this->powerIsCollision = coll; }

	inline int GetBombCollision() { return this->bombIsCollision; }
	inline void SetBombCollision(bool coll) { this->bossIsCollision = coll; }

	inline int GetLifeCollision() { return this->lifeIsCollision; }
	inline void SetLifeCollision(bool coll) { this->lifeIsCollision = coll; }
};

