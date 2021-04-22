#include "StageThreeBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "ZigzagMove.h"
#include "NormalMove.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT StageThreeBoss::Init()
{
    return S_OK;//return Init(nullptr);
}

HRESULT StageThreeBoss::Init(CollisionCheck* collisionCheck, FPOINT* playerPos)
{
    this->collisionCheck = collisionCheck;

    // ����3 �̹���
    currMoveInterface = nullptr;
    image = ImageManager::GetSingleton()->FindImage("StageThreeBoss");
    if (image == nullptr)
    { 
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    isActBarrelCount = 1;
    zigzagFireCount = 4;
    currFrameX = 0;
    updateCount = 0;
    Attackstatus = 0;
    Movestatus = 0;
    pos.x = WINSIZE_X / 2 ;
    pos.y = -150;
    size = 150;
    life = 100;
    moveSpeed = 100.0f;
    TornadoFireCount = 30;
    isAlive = true;
   
    //�̵����⼳��
    moveManager = new MoveManager();
    moveManager->SetMoveSpeed(moveSpeed);
    AttackElapesdTimer = 0.0f;
    AttackTimer = 0.0f;
    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::ZIGZAG_MOVE] = new ZigzagMove;
    vMoveInterfaces[MOVETYPE::NORMAL_MOVE] = new NormalMove;
    /*  vMoveInterfaces[MOVETYPE::SPEAR_MOVE] = new SpearMove;
    vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE] = new BilliardsMove;*/
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);
    
    vBarrels.resize(6);
    for (int i = 0; i < vBarrels.size(); i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(this->collisionCheck, pos.x, pos.y);
        //vBarrels[i]->Init(pos);
        //RotateBarrel(vBarrels[i] , i);
       // vBarrels[i]->SetbarrelEnd();
    }

    return S_OK;
}

void StageThreeBoss::Release()
{
   
    for (int i = 0; i < vBarrels.size(); i++)
    {
        if (vBarrels[i])
            SAFE_RELEASE(vBarrels[i]);
    }
    vBarrels.clear();

    SAFE_DELETE(moveManager);
    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if (vMoveInterfaces[i])
            SAFE_DELETE(vMoveInterfaces[i]);
    }
    vMoveInterfaces.clear();
}

void StageThreeBoss::Update()
{
    //�浹�ڽ� �Ѱ��ֱ�
    //bossRect = { (LONG)(pos.x - size / 2), (LONG)(pos.y - size / 2), (LONG)(pos.x + size / 2), (LONG)(pos.y + size / 2) };
    //(this->collisionCheck)->SetBossRect(bossRect);
    //(this->collisionCheck)->GetBossAlive(isAlive);

    for (int i = 0; i < vBarrels.size(); i++)
    {
        if (vBarrels[i])
        {           
            if (i < isActBarrelCount)
            {
                vBarrels[i]->SetActivated(true);
            }
            else
            {
                vBarrels[i]->SetActivated(false);
            }
            vBarrels[i]->SetBarrelPos(pos);
            // RotateBarrel(vBarrels[i], i); //������ ������ ����
            //vBarrels[i]->SetPos(pos);
        }
    }

    Move();
    
    //�̻��� �߻�
    Attack();

    if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
    {
        life -= 25;
    }
}

void StageThreeBoss::Render(HDC hdc)
{
    if (isAlive)
    {
        //RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            if (!isAlive)
                image->AlphaRender(hdc, pos.x, pos.y, true);
            if (isAlive)
                image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }

        //����
        for (int i = 0; i < vBarrels.size(); i++)
        {
            if (vBarrels[i])
            {
                vBarrels[i]->Render(hdc);
            }
        }
        wsprintf(szText, "BOSS_LIFE: %d", life);
        TextOut(hdc, WINSIZE_X - 150, 120, szText, strlen(szText));
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
        AttackElapesdTimer = TimerManager::GetSingleton()->getElapsedTime();
        AttackTimer += AttackElapesdTimer;
       
        //�̻��� �߻�
        if (Attackstatus == 1)
        {
           
                for (int i = 0; i < 1; i++)
                {

                    if (vBarrels[i]) //���� ������ ���⼭ ������ҰŰ�����
                    {
                        //if(BossHp/4*3>)

                        vBarrels[i]->Attack();
                        vBarrels[i]->SetMaxFireCount(TornadoFireCount);
                        vBarrels[i]->SetFireType(FIRETYPE::TornadoFIRE);
                       
                        vBarrels[i]->Update();
                    }
                }
            
        }
        if (Attackstatus == 2)
        {
            if ((int)AttackTimer % 2 == 0)
            {
                for (int i = 0; i < 1; i++)
                {
                    if (vBarrels[i]) //���� ������ ���⼭ ������ҰŰ�����
                    {
                        //if(BossHp/4*3>)
                        vBarrels[i]->Attack();
                        vBarrels[i]->SetMaxFireCount(zigzagFireCount);
                        vBarrels[i]->SetFireType(FIRETYPE::ZigzagFIRE);
                        vBarrels[i]->Update();
                    }
                }
            }
        } 
    }

    //myMissile->SetPos(pos);
}

void StageThreeBoss::Move()
{    
    MoveElapesdTimer =TimerManager::GetSingleton()->getElapsedTime();//�Ȱ��� �ӵ��� ���������� ���¹�� �߽����� �о��ָ� �ǳ�?
    MoveTimer += MoveElapesdTimer;

    if (Movestatus == 0)//���� �̵�
    {  
        moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);//�̰� �������� �ȵǰ��־���
        currMoveInterface = vMoveInterfaces[MOVETYPE::NORMAL_MOVE];
        moveSpeed = 100;
        moveManager->SetMoveSpeed(moveSpeed);
     
       if (MoveTimer > 3)
       { 
           moveSpeed = 0;
           moveManager->SetMoveSpeed(moveSpeed);    
           Attackstatus = 1;
       }
       if (MoveTimer > 15)
       {
           Attackstatus = 2;
           Movestatus++;
       }      
    }

    if (Movestatus == 1)
    {
       moveSpeed = 2;
       moveManager->SetMoveSpeed(moveSpeed);        
       Movestatus++;
    }

    if (Movestatus == 2)
    {
       moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::ZIGZAG_MOVE]);
       currMoveInterface = vMoveInterfaces[MOVETYPE::ZIGZAG_MOVE];
  
       moveSpeed += 0.001;
       if (moveSpeed > 10)
       {
           Movestatus++;
       }
       moveManager->SetMoveSpeed(moveSpeed);
    }
    if (Movestatus == 3)
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
            (this->collisionCheck)->GetBossAlive(isAlive);
        }
    }
}

void StageThreeBoss::Life(int attackValue)
{
    life -= attackValue;
}
