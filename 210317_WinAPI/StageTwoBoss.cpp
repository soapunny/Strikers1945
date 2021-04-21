#include "StageTwoBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "LeftMove.h"
#include "NormalMove.h"
#include "LeftDownMove.h"
#include "LeftUpMove.h"
#include "RightDownMove.h"
#include "RightUpMove.h"
#include "ComeAndGoMove.h"
#include "RightMove.h"
#include "PhaseChangeMove.h"
#include "CenterMove.h"
#include "LeftSinMove.h"
#include "RightSinMove.h"
#include "BackMove.h"
#include "BossManager.h"

HRESULT StageTwoBoss::Init() 
{
    return S_OK;
}
HRESULT StageTwoBoss::Init(CollisionCheck* collisionCheck, FPOINT* playerPos)
{

    this->collisionCheck = collisionCheck;

    // 보스1 이미지
    image = ImageManager::GetSingleton()->FindImage("StageTwoBoss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currMoveInterface = nullptr;
    currFrameX = 0;
    updateCount = 0;
    life = 1000;
    currTime = 0;
    //보스 
    pos.x = WINSIZE_X / 2;          //위치
    pos.y = 200;
    size = 230;                     //크기
    moveSpeed = 150.0f;               //이동 속도
    angle = 0;
    currElapesdTimer = 0;
    //보스 이동 방법 정의
    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::RIGHT_UP_MOVE] = new RightUpMove;
    vMoveInterfaces[MOVETYPE::CENTER_MOVE] = new CenterMove;
    vMoveInterfaces[MOVETYPE::RIGHT_DOWN_MOVE] = new RightDownMove;
    vMoveInterfaces[MOVETYPE::RIGHT_MOVE ] = new RightMove;
    vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE] = new RightSinMove;
    vMoveInterfaces[MOVETYPE::LEFT_MOVE] = new LeftMove;
    vMoveInterfaces[MOVETYPE::NORMAL_MOVE] = new NormalMove;
    vMoveInterfaces[MOVETYPE::LEFT_DOWN_MOVE] = new LeftDownMove;
    vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE] = new RightSinMove;
    vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE] = new LeftSinMove;
    vMoveInterfaces[MOVETYPE::PHASE_CHANGE_MOVE] = new PhaseChangeMove;
    vMoveInterfaces[MOVETYPE::BACK_MOVE] = new BackMove;
    moveManager = new MoveManager();

    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::CENTER_MOVE]);
    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if (vMoveInterfaces[i])
            vMoveInterfaces[i]->SetMoveSpeed(moveSpeed);
    }

    phase = Phase0;
    state = STATENOT;
    LeftMoving = true;
    //생존여부
    isAlive = true;

    //포신
    vBarrels.resize(6);             //개수는 최대 6개로 지정
    for (int i = 0; i < vBarrels.size(); i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(this->collisionCheck, pos.x,pos.y);
        vBarrels[i]->SetActivated(true);
    }
    
    
    return S_OK;
}

void StageTwoBoss::Release()
{
    for (int i = 0; i < vBarrels.size(); i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->Release();
            delete vBarrels[i];
            vBarrels[i] = nullptr;
        }
    }

    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if (vMoveInterfaces[i])
            SAFE_DELETE(vMoveInterfaces[i]);
    }
}

void StageTwoBoss::Update()
{
    /*srand(time(NULL));
    if(rand() % 300 == 0)
    {
        if (!LeftMoving)
            LeftMoving = true;
        else
            LeftMoving = false;
    }*/
    for (int i = 0; i < vBarrels.size(); i++)
    {
        vBarrels[i]->Update();
    }
    //이동
    Move();
    //미사일 발사
    Attack();

    if (KeyManager::GetSingleton()->IsOnceKeyUp('M'))
    {
        life -= 300;
    }

    for (int i = 0; i < vBarrels.size(); i++)
    {
        if (vBarrels[i]->GetFireType() == FIRETYPE::NormalFIRE)   vBarrels[i]->SetMaxFireCount(50);
        if (vBarrels[i]->GetFireType() == FIRETYPE::TwoFIRE)      vBarrels[i]->SetMaxFireCount(50);
        if (vBarrels[i]->GetFireType() == FIRETYPE::WormFIRE)     vBarrels[i]->SetMaxFireCount(150);
        if (vBarrels[i]->GetFireType() == FIRETYPE::MeteorFIRE)   vBarrels[i]->SetMaxFireCount(150);
        if (vBarrels[i]->GetFireType() == FIRETYPE::TargetFIRE)   vBarrels[i]->SetMaxFireCount(100);
    }
    

    
}

void StageTwoBoss::Render(HDC hdc)
{
    if (isAlive)
    {
        
        //RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);
        if (image)
        {
            if (!isAlive)
                image->AlphaRender(hdc, pos.x, pos.y, true);
            if (isAlive)
            {
                image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true, size);
                //image->AlphaRender(hdc, pos.x, pos.y, true, currFrameX, size);
                //image->AlphaRender(hdc, pos.x, pos.y);
               /* BLENDFUNCTION* blendFunc = image->GetBlendFunc();
               if(blendFunc->SourceConstantAlpha <255) blendFunc->SourceConstantAlpha += 1;*/
                /*if (blendFunc->SourceConstantAlpha < 255)
                    blendFunc->SourceConstantAlpha++;*/
            }
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

void StageTwoBoss::Attack()
{
    if (isAlive)
    {
        //애니메이션
        updateCount++;
        if (updateCount >= 6)
        {
            currFrameX = (currFrameX + 1) % 10;
            updateCount = 0;
        }

        //미사일 발사
        for (int i = 0; i < vBarrels.size(); i++)
        {
            if (vBarrels[i] && vBarrels[i]->GetActivated())
            {
                vBarrels[i]->Update();
                vBarrels[i]->Attack();
            }
        }
    }
}

void StageTwoBoss::Move()
{
    
   // 나중에 상태 개념을 넣어서 상태를 변경 시키면 그에 맞는 행동을 하도록
   // 지금은 페이즈 라는 상태 밖에 없지만 페이즈의 하위로 상태에 맞춰 어택(섞어서 사용)과 무브를 함
   // 예를 들어 1번과 3번 공격을 하면서 4번 무빙을 하는 상태 등 그리고 상태에 쿨타임과 우선순위를 부여
   // 
   // 보스 이동 업데이트
    MoveInterface* currMoveInterface = nullptr;
    currElapesdTimer = TimerManager::GetSingleton()->getElapsedTime();//똑같은 속도로 나선형으로 도는방법 중심점만 밀어주면 되나?
    currTime += currElapesdTimer;
    currTime++;
    
    switch (phase)
    {
    case StageTwoBoss::Phase0:
        if(currTime%2 == 0)size++;
        if (currTime >= 300)
        {
            phase = Phase1;
        }
        else StateType(STATENOT);
        break;
    case StageTwoBoss::Phase1:        
        if (pos.y >= (WINSIZE_Y / 2)-50) backMove();
        else {
            if (currTime <= 500)  StateType(STATE1);
            else if (currTime > 500 && currTime <= 1000) StateType(STATE2);
            else if (currTime > 1000 && currTime <= 1500)  StateType(STATE3);
            else StateType(STATENOT);
            if (currTime == 1500)  currTime = 0;

            if (life <= 700) { phase = Phase2; changePhase = true; currTime = 0; }
        }
       break;
   case StageTwoBoss::Phase2:
       if (changePhase)
           phaseChangeMove();
       if (pos.y >= 250) changePhase = false;
       if (pos.y >= (WINSIZE_Y / 2) - 50) backMove();
       else {
           if (!changePhase)
           {
               if (currTime <= 500)  StateType(STATE4);
               else if (currTime > 500 && currTime <= 1000)  StateType(STATE3);
               else if (currTime > 1000 && currTime <= 1500)  StateType(STATE4);
               else if (currTime > 1500 && currTime <= 2000)  StateType(STATE5);
               else if (currTime > 2000 && currTime <= 2500) StateType(STATE4);
               else if (currTime == 2500)  currTime = 0;
               else StateType(STATENOT);
               if (life <= 400) { phase = Phase3; currTime = 0; }
           }
       }
       break;
   case StageTwoBoss::Phase3:
       if (changePhase)
           phaseChangeMove();
       if (pos.y >= 250) changePhase = false;
       if (pos.y >= (WINSIZE_Y / 2) - 50) backMove();
       else {
           if (!changePhase)
           {
               if (currTime <= 500)  StateType(STATE4);
               else if (currTime > 500 && currTime <= 1000)  StateType(STATE5);
               else if (currTime > 1000 && currTime <= 1500)  StateType(STATE6);
               else if (currTime > 1500 && currTime <= 2000)  StateType(STATE7);
               else if (currTime > 2000 && currTime <= 2500)  StateType(STATE8);
               else StateType(STATENOT);
               if (currTime >= 2500)  currTime = 0;
               if (life <= 0) { phase = Dead; currTime = 0; }
           }
       }
       break;
   case StageTwoBoss::Dead:
       isAlive = false;
       break;
   default:
       break;
   }
    moveManager->SetMoveSpeed(moveSpeed);
    moveManager->DoMove(&pos, &angle);
    
    if (vBarrels[0])//중앙 위
    {
        vBarrels[0]->SetSize(10);
        barrelPos.x = pos.x + 0;
        barrelPos.y = pos.y-20;
        vBarrels[0]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[1])//왼쪽 아래
    {
        vBarrels[1]->SetSize(10);
        barrelPos.x = pos.x - 100;
        barrelPos.y = pos.y+110;
        vBarrels[1]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[2])//왼쪽 위
    {
        vBarrels[2]->SetSize(10);
        barrelPos.x = pos.x - 100;
        barrelPos.y = pos.y - 0;
        vBarrels[2]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[3])//오른쪽 아래
    {
        vBarrels[3]->SetSize(10);
        barrelPos.x = pos.x + 100;
        barrelPos.y = pos.y+110;
        vBarrels[3]->SetBarrelPos(barrelPos);
        
    }
    if (vBarrels[4])//오른쪽 위
    {
        vBarrels[4]->SetSize(10);
        barrelPos.x = pos.x + 100;
        barrelPos.y = pos.y - 0;
        vBarrels[4]->SetBarrelPos(barrelPos);
    }  
    if (vBarrels[5])//중앙 위
    {
        vBarrels[5]->SetSize(10);
        barrelPos.x = pos.x + 0;
        barrelPos.y = pos.y + 120;
        vBarrels[5]->SetBarrelPos(barrelPos);
    }
    
}

void StageTwoBoss::RotateBarrel(float angle)
{
}

void StageTwoBoss::OnDead()
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


void StageTwoBoss::StateType(STATE state)
{

    if(state == STATE1)
    {
#pragma region 와리가리무빙        ;
        if (LeftMoving)
        {
            if (pos.x >= 550)changeRightUpMove();
            else if (pos.x <= 450 && pos.x > 350)changeRightDownMove();
            else if (pos.x <= 350 && pos.x > 250)changeRightUpMove();
            else if (pos.x <= 250 && pos.x > 150)changeRightDownMove();
            else if (pos.x <= 150 && pos.x > 50)changeRightUpMove();
            else if (pos.x <= 50)
                LeftMoving = false;
        }
        if (!LeftMoving)
        {
            if (pos.x <= 50) changeLeftDownMove();
            else if (pos.x >= 150 && pos.x < 250) changeLeftUpMove();
            else if (pos.x >= 250 && pos.x < 350) changeLeftDownMove();
            else if (pos.x >= 350 && pos.x < 450)changeLeftUpMove();
            else if (pos.x >= 450 && pos.x < 550)changeLeftDownMove();
            else if (pos.x >= 550)LeftMoving = true;
        }
#pragma endregion
#pragma endregion

        vBarrels[0]->SetActivated(false);
        vBarrels[1]->SetActivated(true);
        vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[2]->SetActivated(false);
        vBarrels[3]->SetActivated(true);
        vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[4]->SetActivated(false);
        vBarrels[5]->SetActivated(true);
        vBarrels[5]->SetFireType(FIRETYPE::TargetFIRE);
    }

    else if (state == STATE2)
    {
#pragma region 반대끝무빙
        if (LeftMoving)
        {
            changeLeftMove();;
            if (pos.x <= 50)
                LeftMoving = false;
        }
        if (!LeftMoving)
        {
            changeRightMove();
            if (pos.x >= 550)LeftMoving = true;
        }
#pragma endregion
        vBarrels[0]->SetActivated(false);
        vBarrels[1]->SetActivated(false);
         vBarrels[2]->SetActivated(true);
        vBarrels[2]->SetFireType(FIRETYPE::TwoFIRE); vBarrels[2]->SetMissileSize(50);
        vBarrels[3]->SetActivated(false);
         vBarrels[4]->SetActivated(true);
        vBarrels[4]->SetFireType(FIRETYPE::TwoFIRE); vBarrels[4]->SetMissileSize(50);
        vBarrels[5]->SetActivated(true);
        vBarrels[5]->SetFireType(FIRETYPE::TargetFIRE);
    }

    else if (state == STATE3)
    {
#pragma region 반대끝무빙
        if (LeftMoving)
        {
            changeLeftMove();;
            if (pos.x <= 50)
                LeftMoving = false;
        }
        if (!LeftMoving)
        {
            changeRightMove();
            if (pos.x >= 550)LeftMoving = true;
        }
#pragma endregion
         vBarrels[0]->SetActivated(true);
        vBarrels[0]->SetFireType(FIRETYPE::WormFIRE); vBarrels[0]->SetMissileSize(50);
        vBarrels[1]->SetActivated(false);
        vBarrels[2]->SetActivated(false);
        vBarrels[3]->SetActivated(false);
        vBarrels[5]->SetActivated(true);
        vBarrels[5]->SetFireType(FIRETYPE::TargetFIRE);
    }

    else if (state == STATE4)
    {
#pragma region 와리가리무빙
        if (LeftMoving)
        {
            if (pos.x >= 550)changeRightUpMove();
            else if (pos.x <= 450 && pos.x > 350)changeRightDownMove();
            else if (pos.x <= 350 && pos.x > 250)changeRightUpMove();
            else if (pos.x <= 250 && pos.x > 150)changeRightDownMove();
            else if (pos.x <= 150 && pos.x > 50)changeRightUpMove();
            else if (pos.x <= 50)
                LeftMoving = false;
        }
        if (!LeftMoving)
        {
            if (pos.x <= 50) changeLeftDownMove();
            else if (pos.x >= 150 && pos.x < 250) changeLeftUpMove();
            else if (pos.x >= 250 && pos.x < 350) changeLeftDownMove();
            else if (pos.x >= 350 && pos.x < 450)changeLeftUpMove();
            else if (pos.x >= 450 && pos.x < 550)changeLeftDownMove();
            else if (pos.x >= 550)LeftMoving = true;
        }
#pragma endregion
        vBarrels[0]->SetActivated(false);
        vBarrels[1]->SetActivated(true);
        vBarrels[2]->SetActivated(true);
        vBarrels[3]->SetActivated(true);        
        vBarrels[4]->SetActivated(true);
        vBarrels[5]->SetActivated(true);
        vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[2]->SetFireType(FIRETYPE::TwoFIRE); vBarrels[2]->SetMissileSize(50);
        vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[4]->SetFireType(FIRETYPE::TwoFIRE); vBarrels[4]->SetMissileSize(50);
        vBarrels[5]->SetFireType(FIRETYPE::TargetFIRE); vBarrels[5]->SetMissileSize(50);        

    }

    else if (state == STATE5)
    {
#pragma region 센터무빙
        changeCenterMove();
#pragma endregion
        vBarrels[0]->SetActivated(true);
        vBarrels[0]->SetFireType(FIRETYPE::MeteorFIRE); vBarrels[0]->SetMissileSize(35);
        vBarrels[1]->SetActivated(true);
        vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[2]->SetActivated(false);
        vBarrels[3]->SetActivated(true);
        vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[4]->SetActivated(false);
        vBarrels[5]->SetActivated(false);
    }

    else if (state == STATE6)
    {
#pragma region 와리가리무빙
    if (LeftMoving)
    {
        if (pos.x >= 550)changeRightUpMove();
        else if (pos.x <= 450 && pos.x > 350)changeRightDownMove();
        else if (pos.x <= 350 && pos.x > 250)changeRightUpMove();
        else if (pos.x <= 250 && pos.x > 150)changeRightDownMove();
        else if (pos.x <= 150 && pos.x > 50)changeRightUpMove();
        else if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) changeLeftDownMove();
        else if (pos.x >= 150 && pos.x < 250) changeLeftUpMove();
        else if (pos.x >= 250 && pos.x < 350) changeLeftDownMove();
        else if (pos.x >= 350 && pos.x < 450)changeLeftUpMove();
        else if (pos.x >= 450 && pos.x < 550)changeLeftDownMove();
        else if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
        vBarrels[0]->SetActivated(true);
        vBarrels[0]->SetFireType(FIRETYPE::MeteorFIRE); vBarrels[0]->SetMissileSize(35);
        vBarrels[1]->SetActivated(true);
        vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[2]->SetActivated(false);
        vBarrels[0]->SetActivated(true);
        vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[4]->SetActivated(false);
        vBarrels[5]->SetActivated(false);
    }

    else if (state == STATE7)
    {
#pragma region 반대끝무빙
        if (LeftMoving)
        {
            changeLeftMove();;
            if (pos.x <= 50)
                LeftMoving = false;
        }
        if (!LeftMoving)
        {
            changeRightMove();
            if (pos.x >= 550)LeftMoving = true;
        }
#pragma endregion
        vBarrels[0]->SetActivated(true);
        vBarrels[0]->SetFireType(FIRETYPE::WormFIRE);
        vBarrels[1]->SetActivated(false);
        vBarrels[0]->SetActivated(true);
        vBarrels[2]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[3]->SetActivated(false);
        vBarrels[0]->SetActivated(true);
        vBarrels[4]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[5]->SetActivated(false);
    }

    else if (state == STATE8)
    {
#pragma region 센터무빙
        changeCenterMove();
#pragma endregion

        vBarrels[0]->SetActivated(true);
        vBarrels[1]->SetActivated(true);
        vBarrels[2]->SetActivated(true);
        vBarrels[3]->SetActivated(true);
        vBarrels[4]->SetActivated(true);
        vBarrels[0]->SetFireType(FIRETYPE::WormFIRE); vBarrels[0]->SetMissileSize(50);
        vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[2]->SetFireType(FIRETYPE::MeteorFIRE); vBarrels[4]->SetMissileSize(35);
        vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
        vBarrels[4]->SetFireType(FIRETYPE::MeteorFIRE); vBarrels[4]->SetMissileSize(35);
        vBarrels[5]->SetActivated(false);
    }

    else if (state == STATENOT)
    {
        vBarrels[0]->SetActivated(false);
        vBarrels[1]->SetActivated(false);
        vBarrels[2]->SetActivated(false);
        vBarrels[3]->SetActivated(false);
        vBarrels[4]->SetActivated(false);
        vBarrels[5]->SetActivated(false);
    }

    else if (state == STATETRUE)
    {
        vBarrels[0]->SetActivated(true);
        vBarrels[1]->SetActivated(true);
        vBarrels[2]->SetActivated(true);
        vBarrels[3]->SetActivated(true);
        vBarrels[4]->SetActivated(true);
        vBarrels[5]->SetActivated(true);
    }

}

void StageTwoBoss::changeRightMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::RIGHT_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_MOVE];
}

void StageTwoBoss::changeLeftMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::LEFT_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_MOVE];
}

void StageTwoBoss::changeRightUpMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::RIGHT_UP_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_UP_MOVE];
}

void StageTwoBoss::changeLeftUpMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::LEFT_UP_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_UP_MOVE];
}

void StageTwoBoss::changeRightDownMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::RIGHT_DOWN_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_DOWN_MOVE];
}

void StageTwoBoss::changeLeftDownMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::LEFT_DOWN_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_DOWN_MOVE];
}

void StageTwoBoss::changeRightSinMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE];
}

void StageTwoBoss::changeLeftSinMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE];
}

void StageTwoBoss::changeCenterMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::CENTER_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::CENTER_MOVE];
}

void StageTwoBoss::changeNormalMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::NORMAL_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::NORMAL_MOVE];
}

void StageTwoBoss::phaseChangeMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::PHASE_CHANGE_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::PHASE_CHANGE_MOVE];
}

void StageTwoBoss::backMove()
{
    moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::BACK_MOVE]);
    currMoveInterface = vMoveInterfaces[MOVETYPE::BACK_MOVE];
}