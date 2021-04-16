#include "Barrel.h"
#include "MissileManager.h"

HRESULT Barrel::Init(FPOINT pos)
{
    //���� ���� �ʿ�
    barrelSize = 100;
    barrelStart.x = pos.x;
    barrelStart.y = pos.y;
    barrelAngle = 3.14f / 4.0f; //������ 45�� 

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
}

void Barrel::Render(HDC hdc)
{
    // ����
    MoveToEx(hdc, barrelStart.x, barrelStart.y, NULL);
    LineTo(hdc, barrelEnd.x, barrelEnd.y );
}
