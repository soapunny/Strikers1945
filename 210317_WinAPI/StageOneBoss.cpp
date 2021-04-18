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
    pos.x = WINSIZE_X-200;          //위치
    pos.y = WINSIZE_Y / 5;
    size = 200;                     //크기
    moveSpeed = 100.0f;               //이동 속도
    angle = PI/3;

    //pos.x = WINSIZE_X+50;          //위치
    //pos.y = WINSIZE_Y / 2;
    //size = 100;                     //크기
    //moveSpeed = 100.0f;               //이동 속도
    //angle = 0;

    //보스 이동 방법 정의
    vMoveInterfaces.resize(4);
    vMoveInterfaces[0] = new RightSinMove;
    vMoveInterfaces[1] = new LeftSinMove;
    vMoveInterfaces[2] = new SpearMove;
    vMoveInterfaces[3] = new BilliardsMove;

    moveManager = new MoveManager();

    moveManager->ChangeMove(vMoveInterfaces[0]);
    for(int i =0;i<vMoveInterfaces.size();i++)
        vMoveInterfaces[i]->SetMoveSpeed(moveSpeed);

    //moveManager->DoMove(&pos, &angle);

    //life = 100;
    life = 100;
    time = 0.0f;

    ////moveManager->ChangeMove(new PointMove());
    //moveManager->ChangeMove(new RightUpMove());
    ////moveManager->ChangeMove(new ZigzagMove());
    //moveManager->DoMove(&pos, &angle);

    //생존여부
    isAlive = true;

    //포신
    vBarrels.resize(6);             //개수는 최대 6개로 지정
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
        SAFE_RELEASE(vBarrels[i]);
    }
    vBarrels.clear();

    SAFE_DELETE(moveManager);

    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        delete vMoveInterfaces[i];
        vMoveInterfaces[i] = nullptr;
    }
}

void StageOneBoss::Update()
{
    if(isAlive){
        //보스 이동 업데이트
        float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
        time += elapsedTime;

        Move();

        //포신 위치
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

        //애니메이션
        updateCount++;
        if (updateCount >= 5)
        {
            currFrameX = (currFrameX + 1) % 10;
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
            moveManager->ChangeMove(vMoveInterfaces[0]);
            currMoveInterface = vMoveInterfaces[0];
        }
        else if ((int)(time / 10.0f) % 2 && currMoveInterface != vMoveInterfaces[1]) {
            moveManager->ChangeMove(vMoveInterfaces[1]);
            currMoveInterface = vMoveInterfaces[1];
        }
    }
    else if (life > 50) {
        if(currMoveInterface != vMoveInterfaces[2]){
            moveManager->ChangeMove(vMoveInterfaces[2]);
            currMoveInterface = vMoveInterfaces[2];
        }
    }
    else if (life > 25) {
        if (currMoveInterface != vMoveInterfaces[3]) {
            moveManager->ChangeMove(vMoveInterfaces[3]);
            currMoveInterface = vMoveInterfaces[3];
        }
    }
    else {
        if (currMoveInterface != vMoveInterfaces[2]) {
            moveManager->ChangeMove(vMoveInterfaces[2]);
            currMoveInterface = vMoveInterfaces[2];
        }
    }
    moveManager->DoMove(&pos, &angle);
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
    //배럴 업데이트 및 미사일 발사
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

