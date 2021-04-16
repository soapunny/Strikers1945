#include "Barrel.h"
#include "MissileManager.h"

HRESULT Barrel::Init(FPOINT pos)
{
    //포신 동적 필요
    barrelSize = 100;
    barrelStart.x = pos.x;
    barrelStart.y = pos.y;
    barrelAngle = 3.14f / 4.0f; //지금은 45도 

    // 미사일
    myMissile = new MissileManager();   //동적 필요
    myMissile->Init(pos);       //
    fireCount = 0;

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
}

void Barrel::Render(HDC hdc)
{
    // 포신
    MoveToEx(hdc, barrelStart.x, barrelStart.y, NULL);
    LineTo(hdc, barrelEnd.x, barrelEnd.y );
}
