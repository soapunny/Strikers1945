#pragma once
#include "Enemy.h"
class BigEnemy : public Enemy
{
public:
	virtual HRESULT Init(int posX = 0, int posY = 0);
};

