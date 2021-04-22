#include "Barrel.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT Barrel::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
    this->collisionCheck = collisionCheck;

    //포신 동적 필요
    barrelSize = 100;
    barrelStart.x = pos.x;
    barrelStart.y = pos.y;
    barrelAngle = -3.14f / 2.0f; //지금은 45도
    maxFireCount = 1;
    dir = 1;
    missileSize = 25;
    // 미사일
    myMissile = new MissileManager();   //동적 필요
    myMissile->Init(this->collisionCheck, pos);
    fireCount = 0;
    isActivated = false;

    return S_OK;
}

void Barrel::Release()
{
    if (myMissile)
    {
        myMissile->Release();
        delete myMissile;
        myMissile = nullptr;
    }
}

void Barrel::Update()
{
    if (myMissile)
    {
        myMissile->SetOwnerType(MissileManager::Boss);
        myMissile->Update();
        myMissile->SetSize(missileSize);
    }
}

void Barrel::Render(HDC hdc)
{
    // 포신
    myMissile->Render(hdc);

    //미사일
    if (myMissile)
    {
        myMissile->Render(hdc);
    }
}

void Barrel::Attack()
{
    if (myMissile)
    {
        // 포신 각도에 따른 좌표 계산
        barrelEnd.x = barrelStart.x + cosf(barrelAngle) * barrelSize;
        barrelEnd.y = barrelStart.y - sinf(barrelAngle) * barrelSize;
        myMissile->SetPos(barrelEnd);

        //myMissile->Update();
         
        fireCount += TimerManager::GetSingleton()->getElapsedTime();
        if ((int)(fireCount) % (maxFireCount) == 1 && isActivated)
        {
            myMissile->Fire(fireType);
            fireCount = 0;
        }
    }
}

void Barrel::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
