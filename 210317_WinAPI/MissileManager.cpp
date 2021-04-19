#pragma once
#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "FireManager.h"
#include "NormalFire.h"
#include "FireworkFire.h"
#include "GuidedFire.h"
#include "PlayerFire.h"
#include "MeteorFire.h"
#include "WormFire.h"
#include "TwoFire.h"
#include "NotFire.h"
#include "ZigzagFire.h"
#include "FallingKnivesFire.h"

HRESULT MissileManager::Init(FPOINT pos)
{
    totalMissileNum = 2000;
    vMissiles.resize(totalMissileNum);
    vector<Missile*>::iterator myIt;
    for (myIt = vMissiles.begin(); myIt != vMissiles.end(); myIt++)
    {
        (*myIt) = new Missile();
        (*myIt)->Init(pos);
        (*myIt)->SetPos(pos);
        (*myIt)->SetStartPos(pos);
    }

    //FallingKnivesFire fkf;
    
    vFireInterfaces.resize(FIRETYPE::END_FIRETYPE);
    vFireInterfaces[FIRETYPE::NormalFIRE] = new NormalFire();
    vFireInterfaces[FIRETYPE::FallingKnivesFIRE] = new FallingKnivesFire();
    vFireInterfaces[FIRETYPE::FIREWORKFIRE] = new FireworkFire();
    vFireInterfaces[FIRETYPE::GuidedFIRE] = new GuidedFire();
    vFireInterfaces[FIRETYPE::MeteorFIRE] = new MeteorFire();
    vFireInterfaces[FIRETYPE::NotFIRE] = new NotFire();
    vFireInterfaces[FIRETYPE::PlayerFIRE] = new PlayerFire();
    vFireInterfaces[FIRETYPE::TwoFIRE] = new TwoFire();
    vFireInterfaces[FIRETYPE::WormFIRE] = new WormFire();
    vFireInterfaces[FIRETYPE::ZigzagFIRE] = new ZigzagFire();


    //어떤 미사일을 장전 시킬 것인가
    fireManager = new FireManager();
    currFire = vFireInterfaces[FIRETYPE::NormalFIRE];
    fireManager->ChangeMove(currFire);

    return S_OK;
}

void MissileManager::Release()
{
    vector<Missile*>::iterator myIt;
    for (myIt = vMissiles.begin(); myIt != vMissiles.end(); myIt++)
    {
        (*myIt)->Release();
        delete (*myIt);
        (*myIt) = nullptr;
    }
    vMissiles.clear();

    SAFE_DELETE(fireManager);
    for (int i = 0; i < vFireInterfaces.size(); i++) {
        if (vFireInterfaces[i])
        {
            SAFE_DELETE(vFireInterfaces[i]);
        }
    }
    vFireInterfaces.clear();
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->SetPlayerPos(this->playerPos);
        vMissiles[i]->SetStartPos(this->missilePos);
        if(this->fireType == FIRETYPE::PlayerFIRE)
            vMissiles[i]->SetAngle(this->missileAngle);
        vMissiles[i]->Update();
    }
}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->Render(hdc);
    }
}

void MissileManager::Fire(FIRETYPE fireType)
{

    //어떤 미사일을 발사 할 것인지 알려주기
    switch (fireType)
    {
        //체인지 무브 안해줘서 해줬음
    case FIRETYPE::NormalFIRE:
        if(currFire != vFireInterfaces[FIRETYPE::NormalFIRE]){
            currFire = vFireInterfaces[FIRETYPE::NormalFIRE];
        }
        break;
    case FIRETYPE::FallingKnivesFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::FallingKnivesFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::FallingKnivesFIRE];
        }
        break;
    case FIRETYPE::FIREWORKFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::FIREWORKFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::FIREWORKFIRE];
        }
        break;
    case FIRETYPE::GuidedFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::GuidedFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::GuidedFIRE];
        }
        break;
    case FIRETYPE::PlayerFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::PlayerFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::PlayerFIRE];
        }
        break; 
    case FIRETYPE::MeteorFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::MeteorFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::MeteorFIRE];
        }
        break;
    case FIRETYPE::WormFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::WormFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::WormFIRE];
        }
        break;
    case FIRETYPE::TwoFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::TwoFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::TwoFIRE];
        }
        break;
    case FIRETYPE::NotFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::NotFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::NotFIRE];
        }
        break;
    case FIRETYPE::ZigzagFIRE:
        if (currFire != vFireInterfaces[FIRETYPE::ZigzagFIRE]) {
            currFire = vFireInterfaces[FIRETYPE::ZigzagFIRE];
        }
        break;
    default:
        break;
    }

    fireManager->DoFire(&vMissiles, nullptr);
}
