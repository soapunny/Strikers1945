#pragma once
#include "Enemy.h"
class SmallEnemy : public Enemy
{
public:
	virtual HRESULT Init(int posX = 0, int posY = 0);
	virtual void Move();
};

