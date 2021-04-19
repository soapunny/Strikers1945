#include "BossManager.h"
#include "StageOneBoss.h"
#include "StageTwoBoss.h"
#include "StageThreeBoss.h"

HRESULT BossManager::Init()
{
    vBoss.resize(3);
    vBoss[0] = new StageOneBoss();
    vBoss[1] = new StageTwoBoss();
    vBoss[2] = new StageThreeBoss();
    for (int i = 0; i < vBoss.size(); i++)
    {
        vBoss[i]->Init();
    }
 
    return S_OK;
}

void BossManager::Release()
{
    vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        (*myIt)->Release();   
        delete (*myIt);
        (*myIt) = nullptr;
    }
    vBoss.clear();
}

void BossManager::Update()
{
    vBoss[1]->GetAlive();
    vBoss[1]->Update();
    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if((*myIt)->GetAlive())
            (*myIt)->Update();
    }*/
}

void BossManager::Render(HDC hdc)
{
    vBoss[1]->GetAlive();
    vBoss[1]->Render(hdc);
    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if ((*myIt)->GetAlive())
            (*myIt)->Render(hdc);
    }*/
}
