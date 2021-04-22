#include "SmallEnemyFactory.h"
#include "SmallEnemy.h"

Enemy* SmallEnemyFactory::CreateEnemy()
{
	return new SmallEnemy;
}
