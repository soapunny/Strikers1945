#include "BossManager.h"
#include "StageOneBoss.h"
#include "StageTwoBoss.h"
#include "StageThreeBoss.h"
#include "SceneManager.h"
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
    if (sceneManagerObserver) //보스죽으면 다음보스나오고 보스죽으면 다음보스나오고
    {        
       sceneManagerObserver->DeadNotify(vBoss[0]->GetAlive(), vBoss[1]->GetAlive(), vBoss[2]->GetAlive());       
    }
       
   
}

HRESULT BossManager::Init()
{
    return Init(nullptr);
}

HRESULT BossManager::Init(FPOINT* playerPos)
{
    vBoss.resize(3);
    vBoss[0] = new StageOneBoss();
    vBoss[1] = new StageTwoBoss();
    vBoss[2] = new StageThreeBoss();
    for (int i = 0; i < vBoss.size(); i++)
    {
        vBoss[i]->Init(playerPos);
    }

    sceneManagerObserver = new SceneManager;
    RegisterObserver(sceneManagerObserver);
    
    return S_OK;
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
    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if((*myIt)->GetAlive())
            (*myIt)->Update();
    }*/
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
