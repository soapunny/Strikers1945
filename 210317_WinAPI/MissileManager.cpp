#include "CommonFunction.h"
#include "MissileManager.h"
#include "Missile.h"
#include "NormalFire.h"
#include "ZigzagFire.h"

HRESULT MissileManager::Init(FPOINT pos)
{
    totalMissileNum = 500;
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

    //� �̻����� ���� ��ų ���ΰ�
    fireManager = new FireManager();
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
    //� �̻����� �߻� �� ������ �˷��ֱ�
    switch (fireType)
    {
    case FIRETYPE::NormalFIRE:
        fireManager->DoFire(&vMissiles);
        break;
    case FIRETYPE::ZigzagFIRE:
        fireManager->DoFire(&vMissiles);
        break;
    default:
        break;
    }
}
