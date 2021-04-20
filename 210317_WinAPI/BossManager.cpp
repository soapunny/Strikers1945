#include "BossManager.h"
#include "StageOneBoss.h"
#include "StageTwoBoss.h"
#include "StageThreeBoss.h"

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
    vBoss.clear();
}

void BossManager::Update()
{
    vBoss[0]->GetAlive();
    vBoss[0]->Update();

    //vBoss[2]->GetAlive();
    //vBoss[2]->Update();

    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if((*myIt)->GetAlive())
            (*myIt)->Update();
    }*/
}

void BossManager::Render(HDC hdc)
{

    vBoss[0]->GetAlive();
    vBoss[0]->Render(hdc);

    //vBoss[2]->GetAlive();
    //vBoss[2]->Render(hdc);

    /*vector<Boss*>::iterator myIt;
    for (myIt = vBoss.begin(); myIt != vBoss.end(); myIt++)
    {
        if ((*myIt)->GetAlive())
            (*myIt)->Render(hdc);
    }*/
}
