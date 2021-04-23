#include "EnemyManager.h"
#include "SmallEnemyFactory.h"
#include "MediumEnemyFactory.h"
#include "BigEnemyFactory.h"
#include "Enemy.h"
#include "CollisionCheck.h"

HRESULT EnemyManager::Init(CollisionCheck* collisionCheck)
{
    this->collisionCheck = collisionCheck;
    vEnemyFactories.resize(ENEMY_FACTORY::END_ENEMY_FACTORY);
    vEnemyFactories[ENEMY_FACTORY::SMALL_ENEMY] = new SmallEnemyFactory;
    vEnemyFactories[ENEMY_FACTORY::MEDIUM_ENEMY] = new MediumEnemyFactory;
    vEnemyFactories[ENEMY_FACTORY::BIG_ENEMY] = new BigEnemyFactory;

    vEnemyInitPos.resize(ENEMY_INIT_POS::ENEMY_INIT_END);
    vEnemyInitPos[ENEMY_INIT_POS::INIT_LEFT].x = WINSIZE_X/5;
    vEnemyInitPos[ENEMY_INIT_POS::INIT_CENTER].x = WINSIZE_X/2;
    vEnemyInitPos[ENEMY_INIT_POS::INIT_RIGHT].x = WINSIZE_X*4/5;

    vEnemyInitPos[ENEMY_INIT_POS::INIT_LEFT].y = 100;
    vEnemyInitPos[ENEMY_INIT_POS::INIT_CENTER].y = 100;
    vEnemyInitPos[ENEMY_INIT_POS::INIT_RIGHT].y = 100;


    maxEnemyCnt = 30;
    vEnemys.resize(maxEnemyCnt);
    for (int i = 0; i < vEnemys.size(); i++)
    {
        if(i/10 == ENEMY_FACTORY::SMALL_ENEMY){
            vEnemys[i] = vEnemyFactories[ENEMY_FACTORY::SMALL_ENEMY]->CreateEnemy();
            vEnemys[i]->SetEnemyType(ENEMY_TYPE::SMALL_ENEMY);
        }
        else if (i / 10 == ENEMY_FACTORY::MEDIUM_ENEMY) {
            vEnemys[i] = vEnemyFactories[ENEMY_FACTORY::MEDIUM_ENEMY]->CreateEnemy();
            vEnemys[i]->SetEnemyType(ENEMY_TYPE::MEDIUM_ENEMY);
        }
        else if (i / 10 == ENEMY_FACTORY::BIG_ENEMY) {
            vEnemys[i] = vEnemyFactories[ENEMY_FACTORY::BIG_ENEMY]->CreateEnemy();
            vEnemys[i]->SetEnemyType(ENEMY_TYPE::BIG_ENEMY);
        }
        else
            break;

        vEnemys[i]->Init(collisionCheck, vEnemyInitPos[i % (ENEMY_INIT_POS::ENEMY_INIT_END)].x, vEnemyInitPos[i % (ENEMY_INIT_POS::ENEMY_INIT_END)].y);
        vEnemys[i]->SetIsAlive(false);
    }

    time = 0.0f;
    createCycle = 3.0f;
    addEnemyToggle = false;

    return S_OK;
}

void EnemyManager::Release()
{
    //반복자(iterator) :  STL 자료구조를 구성하는 원소의 메모리를 저장하는 객체
    for (int i =0;i<vEnemys.size(); i++)
    {
        if (vEnemys[i])
        {
            SAFE_RELEASE(vEnemys[i]);
        }
    }
    vEnemys.clear();

    for (int i = 0; i < vEnemyFactories.size(); i++)
    {
        if (vEnemyFactories[i])
        {
            SAFE_DELETE(vEnemyFactories[i]);
        }
    }
    vEnemyFactories.clear();
}

void EnemyManager::Update()
{
    
    //Enemy Update
    for (auto enemy : vEnemys)
    {
        if (enemy && enemy->GetIsAlive()){
            enemy->Update();
            enemy->SetPlayerPos(this->playerPos);

            enemy->Attack();


            //Enemy가 밖으로 나갔을 경우
            if (enemy->GetPos().y > WINSIZE_Y+ enemy->GetSize()/2)
            {
                enemy->SetIsAlive(false);
            }
        }
    }

    float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
    time += elapsedTime;
    createCycle = (int)time;
    if (createCycle == ENEMY_PATTERN::FIRST_ENEMY_PATTERN)
    {
        if (!addEnemyToggle) {
            AddEnemy(ENEMY_TYPE::SMALL_ENEMY, ENEMY_INIT_POS::INIT_LEFT);
            AddEnemy(ENEMY_TYPE::SMALL_ENEMY, ENEMY_INIT_POS::INIT_CENTER);
            AddEnemy(ENEMY_TYPE::SMALL_ENEMY, ENEMY_INIT_POS::INIT_RIGHT);
            addEnemyToggle = !addEnemyToggle;
        }
    }
    else if (createCycle == ENEMY_PATTERN::SECOND_ENEMY_PATTERN)
    {
        if (addEnemyToggle) {
            AddEnemy(ENEMY_TYPE::MEDIUM_ENEMY, ENEMY_INIT_POS::INIT_CENTER);
            addEnemyToggle = !addEnemyToggle;
        }
    }
    else if (createCycle == ENEMY_PATTERN::THIRD_ENEMY_PATTERN)
    {
        if (!addEnemyToggle) {
            AddEnemy(ENEMY_TYPE::MEDIUM_ENEMY, ENEMY_INIT_POS::INIT_LEFT);
            AddEnemy(ENEMY_TYPE::MEDIUM_ENEMY, ENEMY_INIT_POS::INIT_RIGHT);
            addEnemyToggle = !addEnemyToggle;
        }
    }
    else if (createCycle == ENEMY_PATTERN::FOURTH_ENEMY_PATTERN)
    {
        if (addEnemyToggle) {
            AddEnemy(ENEMY_TYPE::BIG_ENEMY, ENEMY_INIT_POS::INIT_LEFT);
            AddEnemy(ENEMY_TYPE::BIG_ENEMY, ENEMY_INIT_POS::INIT_RIGHT);
            addEnemyToggle = !addEnemyToggle;
        }
    }
    else if (createCycle == ENEMY_PATTERN::END_ENEMYPATTERN)
    {
        time = 0.0f;
    }
}

void EnemyManager::Render(HDC hdc)
{
    for (auto enemy : vEnemys)
    {
        if(enemy && enemy->GetIsAlive())
            enemy->Render(hdc);
    }
}


void EnemyManager::AddEnemy(ENEMY_TYPE enemyType, ENEMY_INIT_POS enemyInitPos)
{
    for (int i = enemyType*10; i < (enemyType+1)*10; i++)
    {
        if (vEnemys[i] && !(vEnemys[i]->GetIsAlive()))
        {
            vEnemys[i]->SetPos(vEnemyInitPos[enemyInitPos]);
            vEnemys[i]->SetIsAlive(true);
            break;
        }
    }
}

void EnemyManager::SetEnemyLife()
{
}
