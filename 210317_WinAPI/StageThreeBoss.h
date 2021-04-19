#pragma once
#include "GameNode.h"
#include "Boss.h"

class StageThreeBoss : public Boss
{
private:
	MoveInterface* currMoveInterface;
	vector<MoveInterface*> vMoveInterfaces;
	float MoveElapesdTimer;
	float AttackElapesdTimer;
	float AttackTimer;
	float MoveTimer;
	int zigzagFireCount;
	FPOINT BerralEnd;
	int MaxBossHp; //�Ƹ� ���߿� �������� �����ҵ�
	int BossHp;
	int status;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void Move();
	virtual void RotateBarrel(Barrel* barrel, int barrelNum);
	virtual void OnDead();
};
