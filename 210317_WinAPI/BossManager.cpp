#include "BossManager.h"
#include "StageOneBoss.h"
#include "StageTwoBoss.h"
#include "StageThreeBoss.h"
#include "SceneManager.h"
#include "ItemManager.h"
#include "CollisionCheck.h"

HRESULT BossManager::Init()
{
    return S_OK;
}

HRESULT BossManager::Init(CollisionCheck* collisionCheck, FPOINT* playerPos)
{
    this->collisionCheck = collisionCheck;

    vBoss.resize(3);
    vBoss[0] = new StageOneBoss();
    vBoss[1] = new StageTwoBoss();
    vBoss[2] = new StageThreeBoss();
    for (int i = 0; i < vBoss.size(); i++)
    {
        vBoss[i]->Init(this->collisionCheck, playerPos);
    }

    sceneManagerObserver = new SceneManager;
    RegisterObserver(sceneManagerObserver);
    isBoss1Alive=true;
    isBoss2Alive=true;
    isBoss3Alive=true;
    AisBoss1Alive = true;
    AisBoss2Alive = true;;
    AisBoss3Alive = true;;
    return S_OK;
}

void BossManager::RegisterObserver(SceneManager* scenemanager)
{
    scenemanager = sceneManagerObserver;
}



void BossManager::UnRegisterObserver()
{
    delete sceneManagerObserver;
    sceneManagerObserver = nullptr;
}


void BossManager::notifyObserve()
{
    if (sceneManagerObserver) 
    {        
        sceneManagerObserver->DeadNotify(vBoss[0]->GetAlive(), vBoss[1]->GetAlive(), vBoss[2]->GetAlive());
    }
}


void BossManager::Release()
{
    for (int i = 0 ;i< vBoss.size();i++)
    {
        if(vBoss[i]){
            SAFE_RELEASE(vBoss[i]);
        }
    }
    UnRegisterObserver();
    vBoss.clear();
}

void BossManager::Update()
{
    vBoss[sceneManagerObserver->GetNextBoss()]->Update();
    vBoss[1]->Update();
    if (!vBoss[0]->GetAlive() && AisBoss1Alive) { isBoss1Alive = false; bossPosItem[0] = vBoss[0]->GetPos(); AisBoss1Alive = false; }
    if (!vBoss[1]->GetAlive() && AisBoss2Alive) { isBoss2Alive = false; bossPosItem[1] = vBoss[1]->GetPos(); AisBoss2Alive = false;}
    if (!vBoss[2]->GetAlive() && AisBoss3Alive) { isBoss3Alive = false; bossPosItem[2] = vBoss[2]->GetPos(); AisBoss3Alive = false;}

    notifyObserve();
}

void BossManager::Render(HDC hdc)
{
    vBoss[sceneManagerObserver->GetNextBoss()]->Render(hdc);
    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if ((*myIt)->GetAlive())
            (*myIt)->Render(hdc);
    }*/
}
