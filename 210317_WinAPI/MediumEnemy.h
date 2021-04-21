#pragma once
#include "Enemy.h"
class MediumEnemy : public Enemy
{
public:
	virtual HRESULT Init(int posX = 0, int posY = 0);
};

