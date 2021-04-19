#pragma once
#include "GameNode.h"

class Missile;
class Enemy;
class PlayerShip;
class FireManager;
class FireInterface;

class MissileManager : public GameNode
{

private:
	vector<Missile*> vMissiles;
	int totalMissileNum;

	FPOINT missilePos;	//미사일 시작점
	float missileAngle;	//미사일 각도

	FireManager* fireManager;
	vector<FireInterface*> vFireInterfaces;
	FireInterface* currFire;

	FPOINT playerPos;

	FIRETYPE fireType;

public:
	HRESULT Init(FPOINT pos);		// 오버라이딩 : 다형성
	
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Fire(FIRETYPE fireType);

	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
	inline void GetPos() { this->missilePos; }
	inline void SetPos(FPOINT pos) { this->missilePos = pos; }
	inline void SetAngle(float angle) { this->missileAngle = angle; }
};

