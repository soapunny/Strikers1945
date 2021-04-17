#include "StageOneBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"
#include "NormalMove.h"
#include "LeftDownMove.h"
#include "RightSideMove.h"
#include "ZigzagMove.h"
HRESULT StageOneBoss::Init()
{
    // ����1 �̹���
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    //���� 
    pos.x = 200;          //��ġ
    pos.y = WINSIZE_Y / 2;
    size = 100;                     //ũ��
    moveSpeed = 3.3f;               //�̵� �ӵ�
    angle = 0;
    //���� �̵� ��� ����
    moveManager = new MoveManager();
    moveManager->ChangeMove(new ZigzagMove());
    moveManager->DoMove(&pos, &angle);

    //��������
    isAlive = true;

    //����
    vBarrels.resize(6);             //������ �ִ� 6���� ����
    for (int i = 0; i < 6; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos);
    }

    return S_OK;
}

void StageOneBoss::Release()
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

    SAFE_DELETE(moveManager);
}

void StageOneBoss::Update()
{
    //���� �̵� ������Ʈ
    moveManager->SetMoveSpeed(moveSpeed);
    moveManager->DoMove(&pos,&angle);

    //���� ��ġ
    for (int i = 0; i < 6; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->SetPos(pos);
        }
    }

    //�̻��� �߻�
    Attack();
}

void StageOneBoss::Render(HDC hdc)
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

void StageOneBoss::Attack()
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
            if (vBarrels[i])
            {
                vBarrels[i]->Update();
            }
        }
    }
}

void StageOneBoss::Move()
{
}

void StageOneBoss::RotateBarrel(float angle)
{
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
