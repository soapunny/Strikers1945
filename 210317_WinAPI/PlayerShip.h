#pragma once
#include "GameNode.h"

class Image;
class MissileManager;

class PlayerShip: public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	//초당 이동거리
	bool isDying;
	bool isAlive;
	bool canMove;

	int currFrameX;

	int size;
	float attackValue;

	char szText[128];
	int playerLife;

	FPOINT collisionSize;

	int barrelSize;
	FPOINT barrelEnd[4];
	float barrelAngle[4];

	MissileManager* myMissile[4];
	int fireCount;

	RECT playerRect;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	void RotateBarrel(float angle);
	void Move();
	void OnDead();
	void Attack(int i);

	FPOINT GetPos() { return this->pos; }

	inline int GetPlayerLife() { return playerLife; }
	inline void SetPlayerLife() { this->playerLife -= 1; }

	inline RECT GetPlayerRect() { return playerRect; }
	inline void SetPlayerRect(int life) { this->playerLife = life; }
};

