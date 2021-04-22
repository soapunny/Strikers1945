#pragma once
#include "Enemy.h"
class BigEnemy : public Enemy
{
public:
	virtual HRESULT Init(CollisionCheck* collisionCheck, int posX = 0, int posY = 0);
};

