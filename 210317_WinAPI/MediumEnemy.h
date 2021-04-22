#pragma once
#include "Enemy.h"
class MediumEnemy : public Enemy
{
public:
	virtual HRESULT Init(CollisionCheck* collisionCheck, int posX = 0, int posY = 0);
};

