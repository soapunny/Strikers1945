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
//상태 1: NORMAL / 와리                     지속시간5 쿨3 우선순위3
//상태 2 : TWO / 좌우                       지속시간5 쿨3 우선순위3
//상태 3 : METEOR / 중앙                    지속시간5 쿨3 우선순위3
//                                                        
//상태 4 : NORMAL + TWO / 와리              지속시간5 쿨3 우선순위3
//상타 5 : WORM / 중앙                      지속시간5 쿨3 우선순위3
//                                                        
//상태 6 : WORM + 상태1 / 와리              지속시간5 쿨3 우선순위3
//상태 7 : METEOR + 상태2 / 좌우            지속시간5 쿨3 우선순위3
//상태 8 : WORM + METEOR + WORM / 중앙      지속시간5 쿨3 우선순위3
