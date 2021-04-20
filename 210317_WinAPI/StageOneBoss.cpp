#include "StageOneBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "NormalMove.h"
#include "LeftDownMove.h"
#include "LeftSinMove.h"
#include "RightSinMove.h"
#include "SpearMove.h"
#include "BilliardsMove.h"
#include "PointMove.h"
#include "LeftUpMove.h"
#include "RightDownMove.h"
#include "RightUpMove.h"
#include "RightSideMove.h"
#include "ZigzagMove.h"

HRESULT StageOneBoss::Init()
{
    // ����1 �̹���
    image = ImageManager::GetSingleton()->FindImage("StageOneBoss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    //���� 
    pos.x = WINSIZE_X-200;          //��ġ
    pos.y = WINSIZE_Y / 5;
    size = 200;                     //ũ��
    moveSpeed = 100.0f;               //�̵� �ӵ�
    angle = PI/3;

    //pos.x = WINSIZE_X+50;          //��ġ
    //pos.y = WINSIZE_Y / 2;
    //size = 100;                     //ũ��
    //moveSpeed = 100.0f;               //�̵� �ӵ�
    //angle = 0;

    //���� �̵� ��� ����
    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE] = new RightSinMove;
    vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE] = new LeftSinMove;
    vMoveInterfaces[MOVETYPE::SPEAR_MOVE] = new SpearMove;
    vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE] = new BilliardsMove;

    moveManager = new MoveManager();

    moveManager->ChangeMove(vMoveInterfaces[0]);
    for(int i =0;i<vMoveInterfaces.size();i++){
        if(vMoveInterfaces[i])
            vMoveInterfaces[i]->SetMoveSpeed(moveSpeed);
    }

    //moveManager->DoMove(&pos, &angle);

    //life = 100;
    life = 100;
    time = 0.0f;

    ////moveManager->ChangeMove(new PointMove());
    //moveManager->ChangeMove(new RightUpMove());
    ////moveManager->ChangeMove(new ZigzagMove());
    //moveManager->DoMove(&pos, &angle);

    //��������
    isAlive = true;

    //����
    vBarrels.resize(6);             //������ �ִ� 6���� ����
    for (int i = 0; i < 6; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos.x, pos.y);
        vBarrels[i]->SetAngle(i * PI/3 - PI*2/3);
    }

    return S_OK;
}

void StageOneBoss::Release()
{
    for (int i = 0; i < 6; i++)
    {
        if(vBarrels[i])
            SAFE_RELEASE(vBarrels[i]);
    }
    vBarrels.clear();

    SAFE_DELETE(moveManager);
    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if(vMoveInterfaces[i])
            SAFE_DELETE( vMoveInterfaces[i]);
    }
    vMoveInterfaces.clear();
}

void StageOneBoss::Update()
{
    bossRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + 150), (LONG)(pos.y + 150) };

    if(isAlive){
        //���� �̵� ������Ʈ
        float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
        time += elapsedTime;

        Move();

        //���� ��ġ
        for (int i = 0; i < 6; i++)
        {
            if (vBarrels[i])
            {
                vBarrels[i]->SetPos(pos);
                if (i < 2) {
                    vBarrels[i]->SetActivated(true);
                }
                else {
                    vBarrels[i]->SetActivated(false);
                }
            }
        }

        //�ִϸ��̼�
        updateCount++;
        if (updateCount >= 5)
        {
            currFrameX = (currFrameX + 1) % 30;
            updateCount = 0;
        }

        Attack();
    }
}
void StageOneBoss::Move()
{
    MoveInterface* currMoveInterface = nullptr;
    if(life > 75){
        if ((int)(time / 10.0f) % 2 == 0 && currMoveInterface != vMoveInterfaces[0]) {
            moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE]);
            currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE];
        }
        else if ((int)(time / 10.0f) % 2 && currMoveInterface != vMoveInterfaces[1]) {
            moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE]);
            currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE];
        }
    }
    else if (life > 50) {
        if(currMoveInterface != vMoveInterfaces[MOVETYPE::SPEAR_MOVE]){
            moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::SPEAR_MOVE]);
            currMoveInterface = vMoveInterfaces[MOVETYPE::SPEAR_MOVE];
        }
    }
    else if (life > 25) {
        if (currMoveInterface != vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE]) {
            moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE]);
            currMoveInterface = vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE];
        }
    }
    else {
        if (currMoveInterface != vMoveInterfaces[MOVETYPE::SPEAR_MOVE]) {
            moveManager->ChangeMove(vMoveInterfaces[MOVETYPE::SPEAR_MOVE]);
            currMoveInterface = vMoveInterfaces[MOVETYPE::SPEAR_MOVE];
        }
    }
    moveManager->DoMove(&pos, &angle);
}

void StageOneBoss::Render(HDC hdc)
{
    if (isAlive)
    {
        //RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            if (!isAlive)
                image->AlphaRender(hdc, pos.x, pos.y, true);
            else if (isAlive)
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

void StageOneBoss::Attack()
{
    //�跲 ������Ʈ �� �̻��� �߻�
    for (int i = 0; i < 6; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->Update();
            if (pos.x > WINSIZE_X/5 && pos.x < WINSIZE_X*4/5) {
                vBarrels[i]->Attack();
            }
        }
    }
}


void StageOneBoss::OnDead()
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

