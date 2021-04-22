#pragma once
#include "GameNode.h"
#include <vector>
#include "MoveManager.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class Barrel;
class CollisionCheck;
class Boss : public GameNode
{
protected:
	CollisionCheck* collisionCheck;
	RECT bossRect;

	char szText[128];
	Image* image;
	int currFrameX;
	int updateCount;
	float angle;
	FPOINT pos;
	int size;		//보스 크기
	float moveSpeed;
	bool isAlive;
	int life;

	vector<Barrel*> vBarrels;

	FPOINT* playerPos;

	MoveManager* moveManager;

public:
	virtual HRESULT Init();
	virtual HRESULT Init(CollisionCheck* collisionCheck, FPOINT* playerPos) 
	{ 
		this->collisionCheck = collisionCheck;
		return S_OK; 
	}
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	/*virtual void Move();
	virtual void RotateBarrel(float angle);*/
	virtual void OnDead();

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }

	inline int GetSize() { return this->size; }

	inline void SetAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetAlive() { return this->isAlive; }

	inline int GetLife() { return this->life; }

	inline RECT GetBossRect() { return bossRect; }

	virtual void Life(int attackValue);
};