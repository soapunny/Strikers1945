#include "StageThreeBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "ZigzagMove.h"
#include "NormalMove.h"
#include "MissileManager.h"

HRESULT StageThreeBoss::Init()
{
    // ����3 �̹���
    image = ImageManager::GetSingleton()->FindImage("StageThreeBoss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;
    status = 0;
    pos.x = WINSIZE_X / 2 ;
    pos.y = 0;
    size = 150;
    BossHp = 100;
    moveSpeed = 10.0f;
    isAlive = true;
   
    //�̵����⼳��
    moveManager = new MoveManager();
    moveManager->ChangeMove(new NormalMove());
    moveManager->SetMoveSpeed(moveSpeed);

    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::ZIGZAG_MOVE] = new ZigzagMove;
     vMoveInterfaces[MOVETYPE::NORMAL_MOVE] = new NormalMove;
    /*  vMoveInterfaces[MOVETYPE::SPEAR_MOVE] = new SpearMove;
    vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE] = new BilliardsMove;*/
    
    vBarrels.resize(6);
    for (int i = 0; i < 6; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos.x, pos.y);
        //vBarrels[i]->Init(pos);

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
            RotateBarrel(vBarrels[i], i); //������ ������ ����
            //vBarrels[i]->SetPos(pos);
        }
    }

  
    Move();
    

    //�̻��� �߻�
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

        //����
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
        //�ִϸ��̼�
        updateCount++;
        if (updateCount >= 5)
        {
            currFrameX = (currFrameX + 1) % 10;
            updateCount = 0;
        }

        //�̻��� �߻�
        for (int i = 0; i < 6; i++)
        {
            
            if (vBarrels[i]) //���� ������ ���⼭ ������ҰŰ�����
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
    if (MoveTimer < 3)
    { 
        
        moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);
       
    }
    if (status == 0)
    {
        moveManager->SetMoveSpeed
    }

    if(MoveTimer>3 && MoveTimer<25) //�ð������� ������ Ȥ�� ü�¿� ����� ���Ҽ��� ����
    {
        moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::ZIGZAG_MOVE]);
       
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

void StageThreeBoss::RotateBarrel(Barrel* barrel,int barrelNum) //�����Լ��ε� �Ű������ٲ� �ǳ�?
{
   /* barrel->GetAngle();
    barrel->GetstartPos().x;
    barrel->GetSize();*/
    //barrel->SetbarrelEnd()
    
    BerralEnd.x = pos.x + cosf(45* barrelNum) * 100; //���� ���� �Լ�ȭ ��Ű��ͱ��ϳ�..
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
