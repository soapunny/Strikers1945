#include "BossManager.h"
#include "StageOneBoss.h"
#include "StageTwoBoss.h"
#include "StageThreeBoss.h"
#include "SceneManager.h"
#include "ItemManager.h"
#include "CollisionCheck.h"
#include "Image.h"
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
   
    currBossNumber = 0;

    frameTime = 0;

    currFrame = 0;
    maxFrame = 16;
    printNumber = 0;
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
    AisBoss2Alive = true;
    AisBoss3Alive = true;
    
    img = ImageManager::GetSingleton()->FindImage("보스폭발");

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
    //if (vBoss[sceneManagerObserver->GetNextBoss()]->GetAlive() == false)
    //{ 
        currBossNumber = sceneManagerObserver->GetNextBoss();
    //}
       // sceneManagerObserver->SetBossNumber
   
    vBoss[sceneManagerObserver->GetNextBoss()]->Update();
    //vBoss[1]->Update();
    if (!vBoss[0]->GetAlive() && AisBoss1Alive) { isBoss1Alive = false; bossPosItem[0] = vBoss[0]->GetPos(); AisBoss1Alive = false; }
    if (!vBoss[1]->GetAlive() && AisBoss2Alive) { isBoss2Alive = false; bossPosItem[1] = vBoss[1]->GetPos(); AisBoss2Alive = false;}
    if (!vBoss[2]->GetAlive() && AisBoss3Alive) { isBoss3Alive = false; bossPosItem[2] = vBoss[2]->GetPos(); AisBoss3Alive = false;}

    notifyObserve();

    
   
}

void BossManager::Render(HDC hdc)
{
    vBoss[sceneManagerObserver->GetNextBoss()]->Render(hdc);
    
    if ( vBoss[currBossNumber]->GetAlive() == true && vBoss[currBossNumber]->GetLife() <= 0 )
    {
        if (img)
        {
            frameTime++;
            if (frameTime % 15 == 0)
            {
                frameTime = 0;
                printNumber++;
                currFrame++;
            }
            if (printNumber > 0) //위아래로 터짐
            { 
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x -40 , vBoss[currBossNumber]->GetPos().y -40 , currFrame, 0, true); //시간차로 터지게하자        
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x -20 , vBoss[currBossNumber]->GetPos().y +90 , currFrame, 0, true);
            }
            if (printNumber > 3) //오른쪽 옆에서 터짐
            {
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x -40 , vBoss[currBossNumber]->GetPos().y  , currFrame-3, 0, true);
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x +30 , vBoss[currBossNumber]->GetPos().y +30 , currFrame-3, 0, true);
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x +50 , vBoss[currBossNumber]->GetPos().y -35 , currFrame-3, 0, true);

            }
           if (printNumber > 6) //중앙위아래
            {
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x     , vBoss[currBossNumber]->GetPos().y -20 , currFrame-6, 0, true);
               img->FrameRender(hdc, vBoss[currBossNumber]->GetPos().x -50 , vBoss[currBossNumber]->GetPos().y +80 , currFrame-6, 0, true);
            }
           
           if (currFrame > maxFrame)
           {
               vBoss[currBossNumber]->SetAlive(false);        
               currFrame = 0;
           }
        } 
    }

}

bool BossManager::GetEnding()
{
    return sceneManagerObserver->GetEnding();
}

void BossManager::SetBossLife()
{
    vBoss[sceneManagerObserver->GetNextBoss()]->Life(attackValue);
}
