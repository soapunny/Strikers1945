#include "BigEnemy.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT BigEnemy::Init(CollisionCheck* collisionCheck, int posX, int posY)
{
    this->collisionCheck = collisionCheck;
    //ufo
    image = ImageManager::GetSingleton()->FindImage("BigEnemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 200;
    name = "BigEnemy";
    moveSpeed = 20.0f;
    isAlive = true;
    angle = -PI / 2;
    target = nullptr;
    dir = 1;

    // 미사일
    myMissile = new MissileManager();
    myMissile->Init(this->collisionCheck, pos);
    fireCount2 = 0;

    fireType = FIRETYPE::TwoFIRE;

    return S_OK;
}
