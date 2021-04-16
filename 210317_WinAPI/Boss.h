#pragma once
#include "GameNode.h"
#include <vector>
#include "MoveManager.h"

// TODO : ��ĳ����, �ٿ�ĳ���� ����
class Image;
class Barrel;

class Boss : public GameNode
{
protected:
	Image* image;
	int currFrameX;
	int updateCount;
	float angle;
	FPOINT pos;
	int size;		//���� ũ��
	float moveSpeed;
	bool isAlive;

	vector<Barrel*> vBarrels;

	MoveManager* moveManager;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void Move();
	virtual void RotateBarrel(float angle);
	virtual void OnDead();

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }

	inline int GetSize() { return this->size; }

	inline void SetAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetAlive() { return this->isAlive; }
};