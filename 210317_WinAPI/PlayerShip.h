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

	Image* lifeImg[5];
	Image* bombImg[3];

	Image* playerExplosion;
	Image* blinkImage;
	Image* retryImage;
	int explosionCurrFrame;
	bool playerExplosionStart;
	int explosionTime;
	int blinkCount;
	bool reAppear;

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
	float fireTime;

	RECT playerRect;
	int playerPower;

	RECT bombRect;
	int tempSize;

	int bombNum;

public:
	HRESULT Init();
	HRESULT Init(CollisionCheck* collisionCheck);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void Attack(int i);

	FPOINT GetPos() { return this->pos; }
	FPOINT* GetLpPos() { return &pos; }

	inline int GetPlayerLife() { return playerLife; }
	inline void SetPlayerLife() { this->playerLife -= 1; }


	inline int GetPlayerAttackValue() { return this->attackValue; }
	inline void SetPlayerAttackValue(int attackValue) { this->attackValue = attackValue; this->playerPower = attackValue; }

	inline RECT GetPlayerRect() { return playerRect; }

	inline bool GetPlayerAlive() { return this->isAlive; }

	inline void SetBombNum() { if (this->bombNum < 3) this->bombNum += 1; }

	//inline void SetLifeNum() { if (playerLife < 5)playerLife += 1; }
	inline void SetPlusPlayerLife() { if (this->playerLife < 5)this->playerLife += 1; }

	inline void SetPowerNum() { if (playerPower < 3) { playerPower += 1; attackValue = playerPower; } }
};


