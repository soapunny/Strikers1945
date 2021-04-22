#pragma once
#include "EnemyFactory.h"

class SmallEnemyFactory: public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy();
};

