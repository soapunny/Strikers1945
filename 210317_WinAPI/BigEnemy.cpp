#include "BigEnemy.h"
#include "MissileManager.h"
#include "CollisionCheck.h"

HRESULT BigEnemy::Init(int posX, int posY)
{//ufo
    image = ImageManager::GetSingleton()->FindImage("BigEnemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 200;
    name = "BigEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 20.0f;
    isAlive = true;
    angle = -PI / 2;
    target = nullptr;
    dir = 1;

    collisionCheck = new CollisionCheck;
    // �̻���
    myMissile = new MissileManager();
    myMissile->Init(collisionCheck, pos);
    fireCount2 = 0;

    fireType = FIRETYPE::TwoFIRE;

    return S_OK;
}
