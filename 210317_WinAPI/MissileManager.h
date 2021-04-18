#pragma once
#include "GameNode.h"
#include <vector>
#include "FireManager.h"

class Missile;
class Enemy;
class PlayerShip;

class MissileManager : public GameNode
{
public:
	enum class FIRETYPE { NormalFIRE, ZigzagFIRE, MeteorFIRE, WormFIRE, TwoFIRE, NotFIRE	};

private:
	vector<Missile*> vMissiles;
	int totalMissileNum;

	FPOINT missilePos;	//�̻��� ������
	float missileAngle;	//�̻��� ����

	int angle_1, angle_2;	//�ɸ�� �̻��� ����
	int angle_3;			//�� ���� �̻��� ����

	FireManager* fireManager;

public:
	HRESULT Init(FPOINT pos);		// �������̵� : ������
	
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void Fire(FIRETYPE fireType);

	inline void GetPos() { this->missilePos; }
	inline void SetPos(FPOINT pos) { this->missilePos = pos; }
	inline void SetAngle(float angle) { this->missileAngle = angle; }
	inline void SetAngle_3() { this->angle_3 = 0; }
};

