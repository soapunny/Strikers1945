#include "SmallEnemy.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT SmallEnemy::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
    this->collisionCheck = collisionCheck;
    //ufo
    image = ImageManager::GetSingleton()->FindImage("SmallEnemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 80;
    name = "SmallEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 100.0f;
    isAlive = true;
    angle = -PI/2;
    target = nullptr;
    dir = 1;

    // 미사일
    myMissile = new MissileManager();
    myMissile->Init(this->collisionCheck, pos);
    fireCount2 = 0;

    fireType = FIRETYPE::NormalFIRE;

    return S_OK;
}

void SmallEnemy::Move()
{
    float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

    angle = angle > 0.0f ? DegToRad(225) : DegToRad(-85);

    pos.x += cosf(angle) * moveSpeed * elapsedTime;
    pos.y -= sinf(angle) * moveSpeed * elapsedTime;
}