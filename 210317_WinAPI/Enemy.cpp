#include "Enemy.h"
#include "CommonFunction.h"
#include "Tank.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Enemy::Init(int posX, int posY)
{
    //ufo
    image = ImageManager::GetSingleton()->FindImage("Enemy");
    if (image == nullptr)
    {
        MessageBox(g_hWnd, "enemy�� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
        return E_FAIL;
    }
    currFrameX = 0;
    updateCount = 0;

    pos.x = posX;
    pos.y = posY;
    size = 80;
    name = "NormalEnemy";
    shape = { 0, 0, 0, 0 };
    moveSpeed = 3.3f;
    isAlive = true;
    angle = 0.0f;
    target = nullptr;
    dir = 1;

    // �̻���
    myMissile = new MissileManager();
    myMissile->Init(pos);
    fireCount = 0;
    fireCount2 = 0;
    
    return S_OK;
}

void Enemy::Release()
{
    if (myMissile)
    {
        myMissile->Release();
        delete myMissile;
        myMissile = nullptr;
    }
}

void Enemy::Update()
{
    myMissile->SetPos(pos);
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
        if (myMissile)
        {
            myMissile->Update();
            
            if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
            {
                fireCount++;
                if (fireCount % 20 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::ZigzagFIRE);
                    fireCount = 0;
                }
            }
        }
    }
}

void Enemy::Render(HDC hdc)
{
    if (isAlive)
    {
        RenderEllipseToCenter(hdc, pos.x, pos.y, size, size);

        if (image)
        {
            image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
        }

        //�̻���
        if (myMissile)
        {
            myMissile->Render(hdc);
        }
    }
}

void Enemy::Move()
{
    if (target)
    {
        FPOINT targetPos = target->GetPos();

        // ���� ��ġ���� Ÿ�� ��ġ�� �̵��� �� �ִ� ���� ���ϱ�
        float x = targetPos.x - pos.x;
        float y = targetPos.y - pos.y;

        angle = atan2(y, x);

        pos.x += cosf(angle) * moveSpeed;
        pos.y += sinf(angle) * moveSpeed;
    }
}

void Enemy::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
