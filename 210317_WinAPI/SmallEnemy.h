#pragma once
#include "Enemy.h"
class SmallEnemy : public Enemy
{
public:
	virtual HRESULT Init(CollisionCheck* collisionCheck, int posX = 0, int posY = 0);
	virtual void Move();
};

