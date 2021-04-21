#include "MediumEnemy.h"
#include "MissileManager.h"

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
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    // 미사일
    myMissile = new MissileManager();
    myMissile->Init(pos);
    fireCount = 0;
    fireCount2 = 0;

    return S_OK;
}
