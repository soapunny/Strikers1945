#include "MediumEnemy.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT MediumEnemy::Init(int posX, int posY)
{
    //ufo
    image = ImageManager::GetSingleton()->FindImage("MediumEnemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy에 해당하는 이미지가 추가되지 않았음", "경고", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 120;
    name = "MediumEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 50.0f;
    isAlive = true;
    angle = -PI / 2;
    target = nullptr;
    dir = 1;

    collisionCheck = new CollisionCheck;
    // 미사일
    myMissile = new MissileManager();
    myMissile->Init(collisionCheck, pos);
    fireCount2 = 0;

    fireType = FIRETYPE::TwoFIRE;

    return S_OK;
}
