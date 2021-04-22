#pragma once

class Enemy;
class EnemyFactory
{
public:
	virtual Enemy* CreateEnemy()=0;
};
