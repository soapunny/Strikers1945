#pragma once
#include "GameNode.h"
#include "Boss.h"

class StageTwoBoss :public Boss
{
private:
	enum PHASE{Phase0, Phase1, Phase2, Phase3, Dead};
	vector<MoveInterface*> vMoveInterfaces;
	PHASE phase;
	bool LeftMoving;
	bool changePhase = false;
	int hp;
	MoveInterface* currMoveInterface;
	FPOINT barrelPos;
	int currTime;
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void Move();
	virtual void RotateBarrel(float angle);
	virtual void OnDead();
	void State01();
	void State02();
	void State03();
	void State04();
	void State05();
	void State06();
	void State07();
	void State08();
	void StateNot();
	void changeRightMove();
	void changeLeftMove();
	void changeRightUpMove();
	void changeLeftUpMove();
	void changeRightDownMove();
	void changeLeftDownMove();
	void changeRightSinMove();
	void changeLeftSinMove();
	void changeCenterMove();
	void changeNormalMove();
	

};

