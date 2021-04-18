#include "Barrel.h"
#include "MissileManager.h"

HRESULT Barrel::Init(int posX, int posY)
{
    //���� ���� �ʿ�
    barrelSize = 10;
    barrelStart.x = posX;
    barrelStart.y = posY;
    barrelAngle = DegToRad(-90); //������ 45�� 
    isAlive = true;
    target = nullptr;
    dir = 1;
    // �̻���
    myMissile = new MissileManager();   //���� �ʿ�
    myMissile->Init(pos);       //
    fireCount = 0;
    
    return S_OK;
}

void Barrel::Release()
{
    if (myMissile)
    {
        myMissile->Release();
        delete myMissile;
        myMissile = nullptr;
    }
}

void Barrel::Update()
{
    // ���� ������ ���� ��ǥ ���
    barrelEnd.x = barrelStart.x + cosf(barrelAngle) * barrelSize;
    barrelEnd.y = barrelStart.y - (sinf(barrelAngle) * barrelSize);
    myMissile->SetPos(barrelEnd);
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

            if (missileType == NORMAL)
            {
                fireCount++;
                if (fireCount % 100 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::NormalFIRE);
                    fireCount = 0;
                }
            }
            if (missileType == METEOR)
            {
                fireCount++;
                if (fireCount % 200 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::MeteorFIRE);
                    fireCount = 0;
                }
            }
            if (missileType == WORM)
            {
                fireCount++;
                if (fireCount % 200 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::WormFIRE);
                    fireCount = 0;
                }
            }
            if (missileType == TWO)
            {
                fireCount++;
                if (fireCount % 200 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::TwoFIRE);
                    fireCount = 0;
                }
            }
            if (missileType == NOT)
            {
                fireCount++;
                if (fireCount % 200 == 0)
                {
                    myMissile->Fire(MissileManager::FIRETYPE::NotFIRE);
                    fireCount = 0;
                }
            }
        }
    }
}

void Barrel::Render(HDC hdc)
{
    // ����
    MoveToEx(hdc, barrelStart.x, barrelStart.y, NULL);
    LineTo(hdc, barrelEnd.x, barrelEnd.y );
    if (isAlive)
    {  
        //�̻���
        if (myMissile)
        {
            myMissile->Render(hdc);
        }
    }
}

void Barrel::Move()
{
}

void Barrel::HorizonMove()
{
    if (pos.x > WINSIZE_X || pos.x < 0)
    {
        dir *= -1;
    }
    pos.x += moveSpeed * dir;
}
