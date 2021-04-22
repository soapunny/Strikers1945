#pragma once
#include "EnemyFactory.h"

class BigEnemyFactory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy();
};

