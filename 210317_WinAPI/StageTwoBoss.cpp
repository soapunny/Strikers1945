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

HRESULT StageTwoBoss::Init()
{
    // ����1 �̹���
    image = ImageManager::GetSingleton()->FindImage("StageTwoBoss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currMoveInterface = nullptr;
    currFrameX = 0;
    updateCount = 0;
    hp = 1000;
    currTime = 0;
    //���� 
    pos.x = WINSIZE_X / 2;          //��ġ
    pos.y = -50;
    size = 100;                     //ũ��
    moveSpeed = 100.0f;               //�̵� �ӵ�
    angle = 0;
    //���� �̵� ��� ����
    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::RIGHT_UP_MOVE] = new RightUpMove;
    vMoveInterfaces[MOVETYPE::CENTER_MOVE] = new CenterMove;
    vMoveInterfaces[MOVETYPE::RIGHT_DOWN_MOVE] = new RightDownMove;
    vMoveInterfaces[MOVETYPE::RIGHT_MOVE ] = new RightMove;
    vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE] = new RightSinMove;
    vMoveInterfaces[MOVETYPE::LEFT_MOVE] = new LeftMove;
    vMoveInterfaces[MOVETYPE::NORMAL_MOVE] = new NormalMove;
    vMoveInterfaces[MOVETYPE::LEFT_DOWN_MOVE] = new LeftDownMove;
    moveManager = new MoveManager();

    moveManager->ChangeMove(vMoveInterfaces[0]);
    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if (vMoveInterfaces[i])
            vMoveInterfaces[i]->SetMoveSpeed(moveSpeed);
    }

    phase = Phase0;
    LeftMoving = true;
    //��������
    isAlive = true;

    //����
    vBarrels.resize(5);             //������ �ִ� 6���� ����
    for (int i = 0; i < 5; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos.x,pos.y);
        vBarrels[i]->SetActivated(true);
    }
    
    return S_OK;
}

void StageTwoBoss::Release()
{
    for (int i = 0; i < 5; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->Release();
            delete vBarrels[i];
            vBarrels[i] = nullptr;
        }
    }
}

void StageTwoBoss::Update()
{
    for (int i = 0; i < 5; i++)
    {
        vBarrels[i]->Update();
    }
    //�̵�
    Move();
    //�̻��� �߻�
    Attack();

    if (KeyManager::GetSingleton()->IsStayKeyDown('M'))
    {
        hp -= 300;
    }

    for(int i = 0; i<5; i++)
    {
        if (vBarrels[i]->GetFireType() == FIRETYPE::NormalFIRE)   vBarrels[i]->SetMaxFireCount(200);
        if (vBarrels[i]->GetFireType() == FIRETYPE::TwoFIRE)      vBarrels[i]->SetMaxFireCount(200);
        if (vBarrels[i]->GetFireType() == FIRETYPE::WormFIRE)     vBarrels[i]->SetMaxFireCount(50);
        if (vBarrels[i]->GetFireType() == FIRETYPE::MeteorFIRE)   vBarrels[i]->SetMaxFireCount(300);
    }
    

    
}

void StageTwoBoss::Render(HDC hdc)
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
        for (int i = 0; i < 5; i++)
        {
            if (vBarrels[i])
            {
                vBarrels[i]->Render(hdc);
            }
        }
    }
}

void StageTwoBoss::Attack()
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
        for (int i = 0; i < 5; i++)
        {
            if (vBarrels[i])
            {
                vBarrels[i]->Update();
            }
        }
    }
}

void StageTwoBoss::Move()
{
   // ���߿� ���� ������ �־ ���¸� ���� ��Ű�� �׿� �´� �ൿ�� �ϵ���
   // ������ ������ ��� ���� �ۿ� ������ �������� ������ ���¿� ���� ����(��� ���)�� ���긦 ��
   // ���� ��� 1���� 3�� ������ �ϸ鼭 4�� ������ �ϴ� ���� �� �׸��� ���¿� ��Ÿ�Ӱ� �켱������ �ο�
   // 
   // ���� �̵� ������Ʈ
    MoveInterface* currMoveInterface = nullptr;
    currTime++;
    switch (phase)
    {
    case StageTwoBoss::Phase0:
        if (pos.y >= 150) phase = Phase1;
        break;
    case StageTwoBoss::Phase1:
        if (currTime <= 1000)  State01();
        else if (currTime > 1000 && currTime < 1500)  State02();
        else if (currTime > 1500 && currTime < 2000)  State03();
        else StateNot();
        if (currTime == 2000)  currTime = 0;

        if (hp <= 700) {phase = Phase2; changePhase = true; currTime = 0;}
       break;
   case StageTwoBoss::Phase2:
       if(changePhase)
           moveManager->ChangeMove(new PhaseChangeMove());
       if (pos.y >= 250) changePhase = false;
       if (!changePhase)
       {
           if (currTime < 1000)  State04();
           else if (currTime > 1000 &&currTime < 1500)  State03();
           else if (currTime > 1500 &&currTime < 2000)  State04();
           else if (currTime > 2000 &&currTime < 2500)  State05();
           else if (currTime > 2500 &&currTime < 3000)  State04();
           else if (currTime == 3000)  currTime = 0;
           else StateNot();
           if (hp <= 400) { phase = Phase3; currTime = 0; }
       }
       break;
   case StageTwoBoss::Phase3:
       if (changePhase)
           moveManager->ChangeMove(new PhaseChangeMove());
       if (pos.y >= 250) changePhase = false;
       if (!changePhase)
       {
           if (currTime < 1000)  State04();
           else if (currTime > 1000 && currTime < 1500)  State04();
           else if (currTime > 1500 && currTime < 2000)  State06();
           else if (currTime > 2000 && currTime < 2500)  State07();
           else if (currTime > 2500 && currTime < 3000)  State08();
           else StateNot();
           if (currTime >= 3000)  currTime = 0;
       }
       break;
   case StageTwoBoss::Dead:
       break;
   default:
       break;
   }
    moveManager->SetMoveSpeed(moveSpeed);
    moveManager->DoMove(&pos, &angle);
    
    if (vBarrels[0])//�߾�
    {
        vBarrels[0]->SetSize(10);
        barrelPos.x = pos.x + 0;
        barrelPos.y = pos.y-20;
        vBarrels[0]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[1])//���� �Ʒ�
    {
        vBarrels[1]->SetSize(10);
        barrelPos.x = pos.x - 65;
        barrelPos.y = pos.y+55;
        vBarrels[1]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[2])//���� ��
    {
        vBarrels[2]->SetSize(10);
        barrelPos.x = pos.x - 32;
        barrelPos.y = pos.y - 55;
        vBarrels[2]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[3])//������ �Ʒ�
    {
        vBarrels[3]->SetSize(10);
        barrelPos.x = pos.x + 65;
        barrelPos.y = pos.y+55;
        vBarrels[3]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[4])//������ ��
    {
        vBarrels[4]->SetSize(10);
        barrelPos.x = pos.x + 32;
        barrelPos.y = pos.y - 55;
        vBarrels[4]->SetBarrelPos(barrelPos);
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

void StageTwoBoss::State01()
{
#pragma region �͸���������
    if (LeftMoving)
    {
        if (pos.x >= 550)changeRightUpMove();
        if (pos.x <= 450)changeRightDownMove();
        if (pos.x <= 350)changeRightUpMove();
        if (pos.x <= 250) changeRightDownMove();
        if (pos.x <= 150)changeRightUpMove();
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) changeLeftDownMove();
        if (pos.x >= 150)changeLeftUpMove();
        if (pos.x >= 250)changeLeftDownMove();
        if (pos.x >= 350)changeLeftUpMove();
        if (pos.x >= 450)changeLeftDownMove();
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion

    vBarrels[0]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NotFIRE);
}

void StageTwoBoss::State02()
{
#pragma region �ݴ볡����
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
    vBarrels[0]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::TwoFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::TwoFIRE);
}

void StageTwoBoss::State03()
{
#pragma region ��Ʈ����
    changeCenterMove();
#pragma endregion
    vBarrels[0]->SetFireType(FIRETYPE::WormFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NotFIRE);
}

void StageTwoBoss::State04()
{
#pragma region �͸���������
    if (LeftMoving)
    {
        if (pos.x >= 550)changeRightUpMove();
        if (pos.x <= 450)changeRightDownMove();
        if (pos.x <= 350)changeRightUpMove();
        if (pos.x <= 250) changeRightDownMove();
        if (pos.x <= 150)changeRightUpMove();
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) changeLeftDownMove();
        if (pos.x >= 150)changeLeftUpMove();
        if (pos.x >= 250)changeLeftDownMove();
        if (pos.x >= 350)changeLeftUpMove();
        if (pos.x >= 450)changeLeftDownMove();
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::TwoFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::TwoFIRE);

}

void StageTwoBoss::State05()
{
#pragma region ���͹���
    changeCenterMove();
#pragma endregion
    vBarrels[0]->SetFireType(FIRETYPE::MeteorFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NotFIRE);
}


void StageTwoBoss::State06()
{
#pragma region �͸���������
    if (LeftMoving)
    {
        if (pos.x >= 550)changeRightUpMove();
        if (pos.x <= 450)changeRightDownMove();
        if (pos.x <= 350)changeRightUpMove();
        if (pos.x <= 250) changeRightDownMove();
        if (pos.x <= 150)changeRightUpMove();
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) changeLeftDownMove();
        if (pos.x >= 150)changeLeftUpMove();
        if (pos.x >= 250)changeLeftDownMove();
        if (pos.x >= 350)changeLeftUpMove();
        if (pos.x >= 450)changeLeftDownMove();
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetFireType(FIRETYPE::MeteorFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NotFIRE);
}

void StageTwoBoss::State07()
{
#pragma region �ݴ볡����
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
    vBarrels[0]->SetFireType(FIRETYPE::WormFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NormalFIRE);
}

void StageTwoBoss::State08()
{
#pragma region ���͹���
    changeCenterMove();
#pragma endregion
    vBarrels[0]->SetFireType(FIRETYPE::WormFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::MeteorFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NormalFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::MeteorFIRE);
}

void StageTwoBoss::StateNot()
{
    vBarrels[0]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[1]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[2]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[3]->SetFireType(FIRETYPE::NotFIRE);
    vBarrels[4]->SetFireType(FIRETYPE::NotFIRE);
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


