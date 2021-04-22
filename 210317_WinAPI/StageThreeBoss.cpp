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

    // 보스3 이미지
    currMoveInterface = nullptr;
    image = ImageManager::GetSingleton()->FindImage("StageThreeBoss");
    if (image == nullptr)
    { 
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
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
   
    //이동방향설정
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
    //충돌박스 넘겨주기
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
            // RotateBarrel(vBarrels[i], i); //포신의 끝점을 설정
            //vBarrels[i]->SetPos(pos);
        }
    }

    Move();
    
    //미사일 발사
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

        //포신
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
        //애니메이션
        updateCount++;
        if (updateCount >= 5)
        {
            currFrameX = (currFrameX + 1) % 10;
            updateCount = 0;
        }
        AttackElapesdTimer = TimerManager::GetSingleton()->getElapsedTime();
        AttackTimer += AttackElapesdTimer;
       
        //미사일 발사
        if (Attackstatus == 1)
        {
           
                for (int i = 0; i < 1; i++)
                {

                    if (vBarrels[i]) //포신 설정도 여기서 해줘야할거같은데
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
                    if (vBarrels[i]) //포신 설정도 여기서 해줘야할거같은데
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
    MoveElapesdTimer =TimerManager::GetSingleton()->getElapsedTime();//똑같은 속도로 나선형으로 도는방법 중심점만 밀어주면 되나?
    MoveTimer += MoveElapesdTimer;

    if (Movestatus == 0)//등장 이동
    {  
        moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);//이게 값전달이 안되고있었네
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
            (this->collisionCheck)->GetBossAlive(isAlive);
        }
    }
}

void StageThreeBoss::Life(int attackValue)
{
    life -= attackValue;
}
