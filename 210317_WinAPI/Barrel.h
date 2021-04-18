#pragma once
#include "GameNode.h"

class Tank;
class MissileManager;


class Barrel
{
private:

	// 포신(포신의 시작점, 끝점)	동적 필요
	FPOINT barrelStart;
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;
	int currFrameX;
	int updateCount;
	int missileType;
	FPOINT pos;
	int size;
	string name;
	RECT shape;
	float moveSpeed;
	bool isAlive;
	float angle;
	enum MISSILETYPE{NOT,NORMAL, TWO, WORM, METEOR};
	MISSILETYPE typeMissile;
	Tank* target;
	int dir;

	// 미사일
	MissileManager* myMissile; //동적 필요
	int fireCount;
public:
	HRESULT Init(int posX = 0, int posY = 0);
	virtual HRESULT Init() { return E_FAIL; };
	void Release();
	void Update();
	void Render(HDC hdc);

	void Move();
	void HorizonMove();	

	inline void SetBarrelPos(FPOINT pos) { this->barrelStart = pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetTarget(Tank* target) { this->target = target; }
	inline int GetSize() { return this->size; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline void SetMissileType(int type) { this->missileType = type; }
};

