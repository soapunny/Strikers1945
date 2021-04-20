#pragma once
#include "GameNode.h"
#include "Boss.h"

class StageTwoBoss :public Boss
{
private:
	enum PHASE{Phase0, Phase1, Phase2, Phase3, Dead};
	enum STATE { STATE1,STATE2,STATE3, STATE4, STATE5, STATE6,STATE7, STATE8, STATENOT,STATETRUE};
	STATE state;
	vector<MoveInterface*> vMoveInterfaces;
	PHASE phase;
	bool LeftMoving;
	bool changePhase = false;
	int hp;
	MoveInterface* currMoveInterface;
	FPOINT barrelPos;
	int currTime;
	int currElapesdTimer;
public:
	virtual HRESULT Init();
	virtual HRESULT Init(CollisionCheck* collisionCheck, FPOINT* playerPos);
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void Move();
	virtual void RotateBarrel(float angle);
	virtual void OnDead();
	void StateType(STATE state);
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
	void phaseChangeMove();
	void backMove();


};

