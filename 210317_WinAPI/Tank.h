#pragma once
#include "GameNode.h"

/*
	is-a ����		��ũ�� ���ӳ���̴�.
	has-a ����		��ũ�� �̻����� ������ �ִ�.
*/

// ���漱��
//class Enemy;

class Tank : public GameNode
{
private:
	// �Ӽ� : �������
	FPOINT pos;
	int size;
	float attackValue;
	string name;
	RECT shape;

	// ����(������ ������, ����)
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		
	// ����	: �� (degree)		0	~ 180	~ 360
	// ����	: ���� (radian)	0f	~ 3.14f	~ 6.28f

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

