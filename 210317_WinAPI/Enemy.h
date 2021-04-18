#pragma once
#include "GameNode.h"

// TODO : 업캐스팅, 다운캐스팅 설명
class Image;
class Tank;
class MissileManager;

class Enemy : public GameNode
{
private:
	Image* image;
	int currFrameX;
	int updateCount;

	FPOINT playerPos;
	FPOINT pos;
	int size;
	string name;
	RECT shape;
	float moveSpeed;
	bool isAlive;
	float angle;

	Tank* target;
	int dir;

	// 미사일
	MissileManager* myMissile;
	int fireCount;
	int fireCount2;

public:
	HRESULT Init(int posX = 0, int posY = 0);
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	void Move();
	void HorizonMove();

	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
};

