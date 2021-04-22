#pragma once
#include "GameNode.h"

class Image;
class MissileManager;
class CollisionCheck;
class PlayerShip: public GameNode
{
private:
	CollisionCheck* collisionCheck;

	Image* image;
	Image* explosionImage;
	FPOINT pos;
	float moveSpeed;	//초당 이동거리
	bool isDying;
	bool isAlive;
	bool canMove;

	int currFrameX;
	int currFrameX_ex;
	FPOINT exPos;
	float imageTime;
	bool bombUse;

	int size;
	int attackValue;

	char szText[128];
	int playerLife;

	FPOINT collisionSize;
	int barrelSize;
	FPOINT barrelEnd[5];
	bool barrelAlive[5];
	float barrelAngle[5];

	MissileManager* myMissile[5];
	int fireCount;

	RECT playerRect;

	int playerPower;

	RECT bombRect;
	int tempSize;

public:
	HRESULT Init();
	HRESULT Init(CollisionCheck* collisionCheck);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void OnDead();
	void Attack(int i);

	FPOINT GetPos() { return this->pos; }
	FPOINT* GetLpPos() { return &pos; }

	inline int GetPlayerLife() { return playerLife; }
	inline void SetPlayerLife() { this->playerLife -= 1; }

	inline int GetPlayerAttackValue() { return this->attackValue; }
	inline void SetPlayerAttackValue(int attackValue) { this->attackValue = attackValue; this->playerPower = attackValue; }

	inline RECT GetPlayerRect() { return playerRect; }
};

