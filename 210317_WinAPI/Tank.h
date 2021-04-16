#pragma once
#include "GameNode.h"

/*
	is-a 관계		탱크는 게임노드이다.
	has-a 관계		탱크는 미사일을 가지고 있다.
*/

// 전방선언
//class Enemy;

class Tank : public GameNode
{
private:
	// 속성 : 멤버변수
	FPOINT pos;
	int size;
	float attackValue;
	string name;
	RECT shape;

	// 포신(포신의 시작점, 끝점)
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		
	// 단위	: 도 (degree)		0	~ 180	~ 360
	// 단위	: 라디안 (radian)	0f	~ 3.14f	~ 6.28f

public:
	HRESULT Init();

	void Update();		
	void Attack();
	void Move();
	void RotateBarrel(float angle);
	//void Fire();
	//void FireSkill_01();
	//void FireFollowTarget(Enemy* target);

	void Render(HDC hdc);

	void Dead();
	void Release();	

	// get, set
	FPOINT GetPos() { return this->pos; }
};

