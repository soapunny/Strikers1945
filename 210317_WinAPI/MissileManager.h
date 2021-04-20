#pragma once
#include "GameNode.h"

class Missile;
class Enemy;
class PlayerShip;
class FireManager;
class FireInterface;

class MissileManager : public GameNode
{
public:
	

private:
	vector<Missile*> vMissiles;
	int totalMissileNum;

	FPOINT missilePos;	//�̻��� ������
	float missileAngle;	//�̻��� ����

	FireManager* fireManager;
	vector<FireInterface*> vFireInterfaces;
	FireInterface* currFire;

	FPOINT playerPos;

	FIRETYPE fireType;

	int missileSize;

public:
	HRESULT Init(FPOINT pos);		// �������̵� : ������
	
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Fire(FIRETYPE fireType);

	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
	inline void GetPos() { this->missilePos; }
	inline void SetPos(FPOINT pos) { this->missilePos = pos; }
	inline void SetAngle(float angle) { this->missileAngle = angle; }
	inline void SetSize(int size) { this->missileSize = size; }
};

