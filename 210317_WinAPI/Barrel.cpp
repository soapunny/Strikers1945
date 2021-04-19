#include "Barrel.h"
#include "MissileManager.h"

HRESULT Barrel::Init(int posX, int posY)
{
    //포신 동적 필요
    barrelSize = 100;
    barrelStart.x = pos.x;
    barrelStart.y = pos.y;
    barrelAngle = -3.14f / 2.0f; //지금은 45도 
    maxFireCount = 1;
    //barrelSize = 10;
    //barrelStart.x = posX;
    //barrelStart.y = posY;
    //barrelAngle = DegToRad(-90); //지금은 45도 
    //isAlive = true;
    //target = nullptr;
    dir = 1;

    // 미사일
    myMissile = new MissileManager();   //동적 필요
    myMissile->Init(pos);       //
    fireCount = 0;
    maxFireCount = 1;
    isActivated = true;

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
    //Attack();

    myMissile->SetPos(barrelEnd);
  
  
   
     barrelEnd.x = barrelStart.x + cosf(barrelAngle) * barrelSize;
     barrelEnd.y = barrelStart.y - sinf(barrelAngle) * barrelSize;
    
    /*
 
    myMissile->SetPos(barrelEnd);
    if (myMissile)
    {
       myMissile->Update();

        if (KeyManager::GetSingleton()->IsStayKeyDown('W')) 
        {
            fireCount++;
            if (fireCount % 20 == 0)
            {
                myMissile->Fire(MissileManager::FIRETYPE::NormalFIRE);
                fireCount = 0;
            }
        }
        if (KeyManager::GetSingleton()->IsStayKeyDown('Q'))
        {
            fireCount++;
            if (fireCount % 20 == 0)
            {
                myMissile->Fire(MissileManager::FIRETYPE::ZigzagFIRE);
                fireCount = 0;
            }
        }
        if (KeyManager::GetSingleton()->IsStayKeyDown('E'))
        {
            fireCount++;
            if (fireCount % 20 == 0)
            {
                myMissile->Fire(MissileManager::FIRETYPE::NormalFIRE);
                fireCount = 0;
            }
        }
        
    }*/

}

void Barrel::Render(HDC hdc)
{
    // 포신
    myMissile->Render(hdc);
    //MoveToEx(hdc, barrelStart.x, barrelStart.y, NULL);
    //LineTo(hdc, barrelEnd.x, barrelEnd.y );

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
        if (fireCount % maxFireCount == 0 && isActivated)
        {
            myMissile->Fire(fireType);//FIRETYPE::ZigzagFIRE
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
