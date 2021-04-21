#pragma once
#include "EnemyFactory.h"

class MediumEnemyFactory : public EnemyFactory
{
public:
	virtual Enemy* CreateEnemy();
};

