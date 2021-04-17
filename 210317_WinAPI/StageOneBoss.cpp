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
    // 보스1 이미지
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    //보스 
    pos.x = 200;          //위치
    pos.y = WINSIZE_Y / 2;
    size = 100;                     //크기
    moveSpeed = 3.3f;               //이동 속도
    angle = 0;
    //보스 이동 방법 정의
    moveManager = new MoveManager();
    moveManager->ChangeMove(new ZigzagMove());
    moveManager->DoMove(&pos, &angle);

    //생존여부
    isAlive = true;

    //포신
    vBarrels.resize(6);             //개수는 최대 6개로 지정
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
    //보스 이동 업데이트
    moveManager->SetMoveSpeed(moveSpeed);
    moveManager->DoMove(&pos,&angle);

    //포신 위치
    for (int i = 0; i < 6; i++)
    {
        if (vBarrels[i])
        {
            vBarrels[i]->SetPos(pos);
        }
    }

    //미사일 발사
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

void StageOneBoss::Attack()
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
