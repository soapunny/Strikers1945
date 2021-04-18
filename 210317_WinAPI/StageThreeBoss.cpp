#include "StageThreeBoss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"

HRESULT StageThreeBoss::Init()
{
    // ����3 �̹���
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = WINSIZE_X / 2 + 300;
    pos.y = -500;
    size = 100;

    moveSpeed = 3.3f;
    isAlive = true;

    vBarrels.resize(6);
    for (int i = 0; i < 6; i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(pos.x, pos.y);
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
        }
    }

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
            if (vBarrels[i])
            {
                vBarrels[i]->Update();
            }
        }
    }
}

void StageThreeBoss::Move()
{
}

void StageThreeBoss::RotateBarrel(float angle)
{
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
