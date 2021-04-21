#include "MediumEnemyFactory.h"
#include "MediumEnemy.h"

Enemy* MediumEnemyFactory::CreateEnemy()
{
    return new MediumEnemy;
}
