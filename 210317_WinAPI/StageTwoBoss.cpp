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

HRESULT StageTwoBoss::Init()
{
    // ����1 �̹���
    image = ImageManager::GetSingleton()->FindImage("Boss_change");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
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
    moveManager = new MoveManager();
    moveManager->ChangeMove(new NormalMove());
    moveManager->DoMove(&pos, &angle);
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
                image->Render(hdc, pos.x, pos.y, true);
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
    
    if (vBarrels[0])
    {
        barrelPos.x = pos.x + 10;
        barrelPos.y = pos.y;
        vBarrels[0]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[1])
    {
        barrelPos.x = pos.x - 100;
        barrelPos.y = pos.y;
        vBarrels[1]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[2])
    {
        barrelPos.x = pos.x - 100;
        barrelPos.y = pos.y - 100;
        vBarrels[2]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[3])
    {
        barrelPos.x = pos.x + 100;
        barrelPos.y = pos.y;
        vBarrels[3]->SetBarrelPos(barrelPos);
    }
    if (vBarrels[4])
    {
        barrelPos.x = pos.x + 100;
        barrelPos.y = pos.y - 100;
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
        if (pos.x >= 550)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 450)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 350)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 250)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 150)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 150)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 250)moveManager->ChangeMove(new LeftDownMove());           if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 450)moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion

    vBarrels[0]->SetMissileType(0);
    vBarrels[1]->SetMissileType(1);
    vBarrels[2]->SetMissileType(0);
    vBarrels[3]->SetMissileType(1);
    vBarrels[4]->SetMissileType(0);
}

void StageTwoBoss::State02()
{
#pragma region �ݴ볡����
    if (LeftMoving)
    {
        moveManager->ChangeMove(new LeftMove());
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        moveManager->ChangeMove(new RightMove());        
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetMissileType(0);
    vBarrels[1]->SetMissileType(0);
    vBarrels[2]->SetMissileType(2);
    vBarrels[3]->SetMissileType(0);
    vBarrels[4]->SetMissileType(2);
}

void StageTwoBoss::State03()
{
#pragma region ��Ʈ����
    moveManager->ChangeMove(new CenterMove());//���͹���
#pragma endregion
    vBarrels[0]->SetMissileType(3);
    vBarrels[1]->SetMissileType(0);
    vBarrels[2]->SetMissileType(0);
    vBarrels[3]->SetMissileType(0);
    vBarrels[4]->SetMissileType(0);
}

void StageTwoBoss::State04()
{
#pragma region �͸���������
    if (LeftMoving)
    {
        if (pos.x >= 550)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 450)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 350)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 250)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 150)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 150)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 250)moveManager->ChangeMove(new LeftDownMove());           if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 450)moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetMissileType(0);
    vBarrels[1]->SetMissileType(1);
    vBarrels[2]->SetMissileType(2);
    vBarrels[3]->SetMissileType(1);
    vBarrels[4]->SetMissileType(2);

}

void StageTwoBoss::State05()
{
#pragma region ���͹���
    moveManager->ChangeMove(new CenterMove());//���͹���
#pragma endregion
    vBarrels[0]->SetMissileType(4);
    vBarrels[1]->SetMissileType(0);
    vBarrels[2]->SetMissileType(0);
    vBarrels[3]->SetMissileType(0);
    vBarrels[4]->SetMissileType(0);
}


void StageTwoBoss::State06()
{
#pragma region �͸���������
    if (LeftMoving)
    {
        if (pos.x >= 550)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 450)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 350)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 250)moveManager->ChangeMove(new RightDownMove());
        if (pos.x <= 150)moveManager->ChangeMove(new RightUpMove());
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        if (pos.x <= 50) moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 150)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 250)moveManager->ChangeMove(new LeftDownMove());           if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 350)moveManager->ChangeMove(new LeftUpMove());
        if (pos.x >= 450)moveManager->ChangeMove(new LeftDownMove());
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetMissileType(4);
    vBarrels[1]->SetMissileType(1);
    vBarrels[2]->SetMissileType(0);
    vBarrels[3]->SetMissileType(1);
    vBarrels[4]->SetMissileType(0);
}

void StageTwoBoss::State07()
{
#pragma region �ݴ볡����
    if (LeftMoving)
    {
        moveManager->ChangeMove(new LeftMove());
        if (pos.x <= 50)
            LeftMoving = false;
    }
    if (!LeftMoving)
    {
        moveManager->ChangeMove(new RightMove());
        if (pos.x >= 550)LeftMoving = true;
    }
#pragma endregion
    vBarrels[0]->SetMissileType(3);
    vBarrels[1]->SetMissileType(0);
    vBarrels[2]->SetMissileType(2);
    vBarrels[3]->SetMissileType(0);
    vBarrels[4]->SetMissileType(2);
}

void StageTwoBoss::State08()
{
#pragma region ���͹���
    moveManager->ChangeMove(new CenterMove());//���͹���
#pragma endregion
    vBarrels[0]->SetMissileType(3);
    vBarrels[1]->SetMissileType(1);
    vBarrels[2]->SetMissileType(4);
    vBarrels[3]->SetMissileType(1);
    vBarrels[4]->SetMissileType(4);
}

void StageTwoBoss::StateNot()
{
    vBarrels[0]->SetMissileType(0);
    vBarrels[1]->SetMissileType(0);
    vBarrels[2]->SetMissileType(0);
    vBarrels[3]->SetMissileType(0);
    vBarrels[4]->SetMissileType(0);
}


