#pragma once
#include "GameNode.h"

class Missile;
class Enemy;
class PlayerShip;
class FireManager;
class FireInterface;
class CollisionCheck;
class MissileManager : public GameNode
{
public:
	//enum FIRETYPE { NormalFIRE, FallingKnivesFIRE, FIREWORKFIRE, GuidedFIRE, PlayerFIRE, ZigzagFIRE, MeteorFIRE, WormFIRE, TwoFIRE, NotFIRE, END_FIRETYPE };
	enum OWNERTYPE { Player, Enemy, Boss };
private:
	CollisionCheck* collisionCheck;
	vector<RECT*>* vMissilesRect;

	vector<Missile*> vMissiles;
	int totalMissileNum;

	FPOINT missilePos;	//미사일 시작점
	float missileAngle;	//미사일 각도

	FireManager* fireManager;
	vector<FireInterface*> vFireInterfaces;
	FireInterface* currFire;

	FPOINT playerPos;

	FIRETYPE fireType;
	OWNERTYPE ownerType;

	int missileSize;

public:
	HRESULT Init(CollisionCheck* collisionCheck, FPOINT pos);		// 오버라이딩 : 다형성

	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Fire(FIRETYPE fireType);

	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
	inline FPOINT GetPos() { return this->missilePos; }
	inline void SetPos(FPOINT pos) { this->missilePos = pos; }
	inline void SetAngle(float angle) { this->missileAngle = angle; }

	inline void SetSize(int size) { this->missileSize = size; }

	inline void SetOwnerType(OWNERTYPE type) { this->ownerType = type; }
	inline int GetTotalMissileNum() { return totalMissileNum; }
	inline vector<Missile*> GetMissileVector() { return vMissiles; }
	inline vector<RECT*>* GetMissileRect() { return vMissilesRect; }

};

