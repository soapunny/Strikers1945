#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "NormalFire.h"
#include "MeteorFire.h"
#include "WormFire.h"
#include "TwoFire.h"
#include "NotFire.h"
#include "ZigzagFire.h"

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

    angle_1 = 0;
    angle_2 = 0;
    angle_3 = 0;

    //어떤 미사일을 장전 시킬 것인가
    fireManager = new FireManager();
    fireManager->ChangeMove(new NormalFire());
    fireManager->ChangeMove(new MeteorFire());
    fireManager->ChangeMove(new WormFire());
    fireManager->ChangeMove(new TwoFire());
    fireManager->ChangeMove(new NotFire());
    //fireManager->ChangeMove(new NormalFire());
    fireManager->ChangeMove(new ZigzagFire());

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
}

void MissileManager::Update()
{
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i]->SetStartPos(this->missilePos);
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
        fireManager->ChangeMove(new NormalFire());
        fireManager->DoFire(&vMissiles);
        break; 
    case FIRETYPE::MeteorFIRE:
        fireManager->ChangeMove(new MeteorFire());
        fireManager->DoFire(&vMissiles);
        break;
    case FIRETYPE::WormFIRE:
        fireManager->ChangeMove(new WormFire());
        fireManager->DoFire(&vMissiles);
        break;
    case FIRETYPE::TwoFIRE:
        fireManager->ChangeMove(new TwoFire());
        fireManager->DoFire(&vMissiles);
        break;
    case FIRETYPE::NotFIRE:
        fireManager->ChangeMove(new NotFire());
        fireManager->DoFire(&vMissiles);
        break;
    case FIRETYPE::ZigzagFIRE:
        fireManager->DoFire(&vMissiles);
        break;
    default:
        break;
    }
}
