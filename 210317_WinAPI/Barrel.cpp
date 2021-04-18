#include "Barrel.h"
#include "MissileManager.h"

HRESULT Barrel::Init(FPOINT pos)
{
    //포신 동적 필요
    barrelSize = 100;
    barrelStart.x = pos.x;
    barrelStart.y = pos.y;
    barrelAngle = -3.14f / 2.0f; //지금은 45도 

    // 미사일
    myMissile = new MissileManager();   //동적 필요
    myMissile->Init(pos);       //
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
    // 포신 각도에 따른 좌표 계산
    barrelEnd.x = barrelStart.x + cosf(barrelAngle) * barrelSize;
    barrelEnd.y = barrelStart.y - (sinf(barrelAngle) * barrelSize);
    if (myMissile)
    {
        myMissile->Update();
    }

}

void Barrel::Render(HDC hdc)
{
    // 포신
    MoveToEx(hdc, barrelStart.x, barrelStart.y, NULL);
    LineTo(hdc, barrelEnd.x, barrelEnd.y );
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
        //myMissile->Update();

        fireCount++;
        myMissile->SetPos(barrelEnd);
        if (fireCount % 100 == 0 && isActivated)
        {
            myMissile->Fire(MissileManager::FIRETYPE::FIREWORKFIRE);
            fireCount = 0;
        }
    }
}
