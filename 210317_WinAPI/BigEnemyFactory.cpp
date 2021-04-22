#include "BigEnemyFactory.h"
#include "BigEnemy.h"

Enemy* BigEnemyFactory::CreateEnemy()
{
    return new BigEnemy;
}
