#include "Boss.h"
#include "CommonFunction.h"
#include "Image.h"
#include "Barrel.h"

HRESULT Boss::Init()
{
    return S_OK;
}

void Boss::Release()
{
}

void Boss::Update()
{
}

void Boss::Attack()
{
}

void Boss::Render(HDC hdc)
{
}

//void Boss::Move()
//{
//}
//
//void Boss::RotateBarrel(float angle)
//{
//}

void Boss::OnDead()
{
}

void Boss::Life(int attackValue)
{
}
//���� 1: NORMAL / �͸�                     ���ӽð�5 ��3 �켱����3
//���� 2 : TWO / �¿�                       ���ӽð�5 ��3 �켱����3
//���� 3 : METEOR / �߾�                    ���ӽð�5 ��3 �켱����3
//                                                        
//���� 4 : NORMAL + TWO / �͸�              ���ӽð�5 ��3 �켱����3
//��Ÿ 5 : WORM / �߾�                      ���ӽð�5 ��3 �켱����3
//                                                        
//���� 6 : WORM + ����1 / �͸�              ���ӽð�5 ��3 �켱����3
//���� 7 : METEOR + ����2 / �¿�            ���ӽð�5 ��3 �켱����3
//���� 8 : WORM + METEOR + WORM / �߾�      ���ӽð�5 ��3 �켱����3
