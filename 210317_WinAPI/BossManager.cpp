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
    
    return S_OK;
}

void BossManager::RegisterObserver(SceneManager* scenemanager)
{
    scenemanager = sceneManagerObserver;
}

void BossManager::RegisterObserver(ItemManager* itemManager)
{
    itemManager = itemManagerObserver;
}

void BossManager::UnRegisterObserver()
{
    delete sceneManagerObserver;
    sceneManagerObserver = nullptr;
}

void BossManager::ItemUnRegisterObserver()
{
    delete itemManagerObserver;
    itemManagerObserver = nullptr;
}

void BossManager::notifyObserve()
{
    if (sceneManagerObserver) 
    {        
        sceneManagerObserver->DeadNotify(vBoss[0]->GetAlive(), vBoss[1]->GetAlive(), vBoss[2]->GetAlive());
    }
}

void BossManager::ItemnotifyObserve()
{
    if (itemManagerObserver) //보스가 죽으면 해당하는 아이템 생성
    {
        
        if (!vBoss[1]->GetAlive()) { itemManagerObserver->SetDropNotify(BOSSDROP); itemManagerObserver->SetDropPos(vBoss[1]->GetPos()); }
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
