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
#include "CollisionCheck.h"
#include "BossManager.h"
HRESULT StageOneBoss::Init()
{
    return S_OK;
}

HRESULT StageOneBoss::Init(CollisionCheck* collisionCheck, FPOINT* playerPos)
{
    this->collisionCheck = collisionCheck;

    // 보스1 이미지
    image = ImageManager::GetSingleton()->FindImage("StageOneBoss");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    //보스 
    pos.x = WINSIZE_X/2;          //위치
    pos.y = WINSIZE_Y / 5;
    size = 150;                     //크기
    moveSpeed = 100.0f;               //이동 속도
    angle = PI / 3;

    //보스 이동 방법 정의
    vMoveInterfaces.resize(MOVETYPE::END_MOVE);
    vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE] = new RightSinMove;
    vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE] = new LeftSinMove;
    vMoveInterfaces[MOVETYPE::SPEAR_MOVE] = new SpearMove;
    vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE] = new BilliardsMove;

    moveManager = new MoveManager();
    currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE];

    moveManager->ChangeMove(currMoveInterface);
    for (int i = 0; i < vMoveInterfaces.size(); i++) {
        if (vMoveInterfaces[i])
            vMoveInterfaces[i]->SetMoveSpeed(moveSpeed);
    }

    //life = 100;
    life = 400;
    time = 0.0f;


    this->playerPos = playerPos;
    
    //생존여부
    isAlive = true;

    //포신
    vBarrels.resize(6);             //개수는 최대 6개로 지정
    for (int i = 0; i < vBarrels.size(); i++)
    {
        vBarrels[i] = new Barrel();
        vBarrels[i]->Init(this->collisionCheck, pos.x, pos.y);
        vBarrels[i]->SetAngle(i * PI / 3 - PI * 2 / 3);
        vBarrels[i]->SetBarrelSize(50);
        vBarrels[i]->SetBarrelPos(pos);
        vBarrels[i]->SetActivated(false);
        vBarrels[i]->SetFireType(FIRETYPE::FallingKnivesFIRE);
        vBarrels[i]->SetMaxFireCount(100);

        //TODO 플레이어 위치 저장
    }

    return S_OK;
}

void StageOneBoss::Release()
{
    for (int i = 0; i < vBarrels.size(); i++)
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
    if(isAlive){
        //충돌박스 넘겨주기
        bossRect = { (LONG)(pos.x - size / 2), (LONG)(pos.y - size / 3), (LONG)(pos.x + size / 2), (LONG)(pos.y + size / 3) };
        (this->collisionCheck)->SetBossRect(bossRect);
        (this->collisionCheck)->GetBossAlive(isAlive);

        //보스 이동 업데이트

        if (KeyManager::GetSingleton()->IsOnceKeyDown('U')) {
            life -= 250;
        }

        Move();

        //포신 위치
        for (Barrel* lpBarrel : vBarrels)
        {
            if (lpBarrel && lpBarrel->GetActivated())
            {
                lpBarrel->SetBarrelPos(pos);//TODO pos가 말도 안되는 값 들어오는 이유 찾기
            }
        }
        if(vBarrels[2] && vBarrels[2]->GetActivated())
            vBarrels[2]->SetBarrelPos(FPOINT{WINSIZE_X-pos.x, WINSIZE_Y-pos.y});

        //애니메이션
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
    if(life > 325){
        float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();
        time += elapsedTime;

        if ((int)time / 5  % 2 == 0 && currMoveInterface != vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE]) {
            currMoveInterface = vMoveInterfaces[MOVETYPE::RIGHT_SIN_MOVE];
            moveManager->ChangeMove(currMoveInterface);
            vBarrels[0]->SetActivated(true);
            vBarrels[1]->SetActivated(true);
            vBarrels[0]->SetFireType(FIRETYPE::NormalFIRE);
            vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        }
        else if ((int)time / 5 % 2 == 1 && currMoveInterface != vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE]) {
            currMoveInterface = vMoveInterfaces[MOVETYPE::LEFT_SIN_MOVE];
            moveManager->ChangeMove(currMoveInterface);
            vBarrels[0]->SetActivated(true);
            vBarrels[1]->SetActivated(true);
            vBarrels[0]->SetFireType(FIRETYPE::NormalFIRE);
            vBarrels[1]->SetFireType(FIRETYPE::NormalFIRE);
        }
    }
    else if (life > 200) {
        if(currMoveInterface != vMoveInterfaces[MOVETYPE::SPEAR_MOVE]){
            currMoveInterface = vMoveInterfaces[MOVETYPE::SPEAR_MOVE];
            currMoveInterface->Renew();
            ((SpearMove*)currMoveInterface)->SetLpPlayerPos(playerPos);
            moveManager->ChangeMove(currMoveInterface);
            vBarrels[0]->SetActivated(false);
            vBarrels[1]->SetActivated(false);
            vBarrels[3]->SetActivated(true);
            vBarrels[4]->SetActivated(true);
            vBarrels[3]->SetFireType(FIRETYPE::FallingKnivesFIRE);
            vBarrels[4]->SetFireType(FIRETYPE::FallingKnivesFIRE);
            vBarrels[3]->SetMaxFireCount(50);
            vBarrels[4]->SetMaxFireCount(50);
        }
    }
    else if (life > 100) {
        if (currMoveInterface != vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE]) {
            currMoveInterface = vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE];
            moveManager->ChangeMove(currMoveInterface);
            vBarrels[3]->SetFireType(FIRETYPE::FIREWORKFIRE);
            vBarrels[3]->SetMaxFireCount(100);
            //vBarrels[4]->SetFireType(FIRETYPE::FIREWORKFIRE);
            vBarrels[4]->SetActivated(false);
            

            vBarrels[2]->SetMaxFireCount(100);
            vBarrels[2]->SetActivated(true);
            vBarrels[2]->SetFireType(FIRETYPE::FIREWORKFIRE);
        }
    }
    else if(life > 0){
        if (currMoveInterface != vMoveInterfaces[MOVETYPE::SPEAR_MOVE]) {
            currMoveInterface = vMoveInterfaces[MOVETYPE::SPEAR_MOVE];
            currMoveInterface->Renew();
            moveManager->ChangeMove(currMoveInterface);
            vBarrels[2]->SetActivated(false);
            vBarrels[4]->SetActivated(true);
            vBarrels[3]->SetFireType(FIRETYPE::FallingKnivesFIRE);
            vBarrels[4]->SetFireType(FIRETYPE::FallingKnivesFIRE);
        }
    }
    else {
        vBarrels[0]->SetActivated(false);
        vBarrels[1]->SetActivated(false);
        vBarrels[2]->SetActivated(false);
        vBarrels[3]->SetActivated(false);
        vBarrels[4]->SetActivated(false);
        vBarrels[5]->SetActivated(false);

        isAlive = false;
        (this->collisionCheck)->GetBossAlive(isAlive);
    }
    moveManager->DoMove(&pos, &angle);
}

void StageOneBoss::Life(int attackValue)
{
    life -= attackValue;
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
            else
            {
                image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
                if(currMoveInterface == vMoveInterfaces[MOVETYPE::BILLIARDS_MOVE]){ 
                    image->FrameRender(hdc, WINSIZE_X - pos.x, WINSIZE_Y - pos.y, currFrameX, 0, true);
                }
            }
        }

        //포신
        for (auto lpBarrel : vBarrels)
        {
            if (lpBarrel)
            {
                lpBarrel->Render(hdc);
            }
        }
        wsprintf(szText, "BOSS[1] LIFE: %d", life);
        TextOut(hdc, WINSIZE_X - 150, 120, szText, strlen(szText));
    }
}

void StageOneBoss::Attack()
{
    //배럴 업데이트 및 미사일 발사
    for (auto lpBarrel: vBarrels)
    {
        if (lpBarrel)
        {
            lpBarrel->Update();
            
            if (lpBarrel->GetActivated() && (pos.x > WINSIZE_X/6 && pos.x < WINSIZE_X*5/6 || pos.y < WINSIZE_Y/2)) {
                lpBarrel->Attack();
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
            //isAlive = false;
        }
    }
}

