#include "StageThreeBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "ZigzagMove.h"
#include "NormalMove.h"
#include "MissileManager.h"

HRESULT StageThreeBoss::Init()
{
    // 보스3 이미지
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = WINSIZE_X / 2 ;
    pos.y = 0;
    size = 150;
    BossHp = 100;
    moveSpeed = 1.0f;
    isAlive = true;
   
    //이동방향설정
    moveManager = new MoveManager();
    moveManager->ChangeMove(new NormalMove());
    moveManager->SetMoveSpeed(moveSpeed);

    
    
    vBarrels.resize(6);
    for (int i = 0; i < 6; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos);
        //RotateBarrel(vBarrels[i] , i);
       // vBarrels[i]->SetbarrelEnd();
    }

  

    return S_OK;
}

void StageThreeBoss::Release()
{
    for (int i = 0; i < 6; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->Release();
            delete vBarrels[i];
            vBarrels[i] = nullptr;
        }
    }
}

void StageThreeBoss::Update()
{
    for (int i = 0; i < 6; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->SetPos(pos);
            RotateBarrel(vBarrels[i], i); //포신의 끝점을 설정
            //vBarrels[i]->SetPos(pos);
        }
    }

  
    Move();
    

    //미사일 발사
    Attack();
}

void StageThreeBoss::Render(HDC hdc)
{
    if (isAlive)
    {
        RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            if (!isAlive)
                image->AlphaRender(hdc, pos.x, pos.y, true);
            if (isAlive)
                image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }

        //포신
        for (int i = 0; i < 6; i++)
        {
            if (vBarrels[i])
            {
                vBarrels[i]->Render(hdc);
            }
        }
    }
}

void StageThreeBoss::Attack()
{
    if (isAlive)
    {
        //애니메이션
        updateCount++;
        if (updateCount >= 5)
        {
            currFrameX = (currFrameX + 1) % 10;
            updateCount = 0;
        }

        //미사일 발사
        for (int i = 0; i < 6; i++)
        {
            
            if (vBarrels[i]) //포신 설정도 여기서 해줘야할거같은데
            {
                vBarrels[i]->Update();
            }
        }
    }

    //myMissile->SetPos(pos);
}

void StageThreeBoss::Move()
{
    MoveElapesdTimer =TimerManager::GetSingleton()->getElapsedTime();
    MoveTimer += MoveElapesdTimer;
    if (MoveTimer > 1)
    { 
        //moveManager->ChangeMove(new ZigzagMove());
        moveManager->ChangeMove(new NormalMove());
       // moveManager->DoMove(&pos, &angle);
    }

    if(MoveTimer>3 && MoveTimer<25) //시간에따라 움직임 혹은 체력에 따라로 변할수도 있음
    {
       
        //moveManager->DoMove(&pos, &angle);
        moveSpeed += 0.001;
        moveManager->SetMoveSpeed(moveSpeed);
    } 
    else
    {

        //moveManager->DoMove(&pos, &angle);
        moveSpeed -= 0.001;
        moveManager->SetMoveSpeed(moveSpeed);
    }
    moveManager->DoMove(&pos, &angle);
    
}

void StageThreeBoss::RotateBarrel(Barrel* barrel,int barrelNum) //가상함수인데 매개변수바뀌어도 되나?
{
   /* barrel->GetAngle();
    barrel->GetstartPos().x;
    barrel->GetSize();*/
    //barrel->SetbarrelEnd()
    
    BerralEnd.x = pos.x + cosf(45* barrelNum) * 100; //숫자 말고 함수화 시키고싶긴하네..
    BerralEnd.y = pos.y - sinf(45* barrelNum) * 100;
    
    barrel->SetbarrelEnd(BerralEnd);
}

void StageThreeBoss::OnDead()
{
    if (image)
    {
        BLENDFUNCTION* blendFunc = image->GetBlendFunc();
        if (blendFunc->SourceConstantAlpha > 0)
        {
            blendFunc->SourceConstantAlpha--;
        }
        else
        {
            isAlive = false;
        }
    }
}
