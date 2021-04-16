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

	int size;
	float attackValue;

	int barrelSize;
	FPOINT barrelEnd;
	FPOINT barrelEnd2;
	FPOINT barrelEnd3;
	float barrelAngle;
	float barrelAngle2;
	float barrelAngle3;

	MissileManager* myMissile[3];
	int fireCount;

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
};

