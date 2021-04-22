#include "WormFire.h"
#include "Missile.h"
#include "CollisionCheck.h"
void WormFire::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos)
{
    this->collisionCheck = collisionCheck;

    vector<Missile*>::iterator myIt;

    //일정 범위 안에서 위로 쭉 쏘아 올리고 
    //작아지면서 해당 위치에 쏘기 그리고 사라짐
    srand(std::time(NULL));

    float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();


    //for (int i=0;i<vMissiles->size();i++)
    //{
    //    if ((*vMissiles)[i]->GetIsFired() == false)
    //    {
    //        randAngle = (rand() % 168 - 18) * 100;
    //        (*vMissiles)[i]->SetType(Missile::SKILLTYPE::WormSKill_TYPE);
    //        (*vMissiles)[i]->SetIsFired(true);
    //        (*vMissiles)[i]->SetAngle(DegToRad(k)/** elapsedTime*1000*/);
    //        k +=10;
    //        break;
    for (int i = 0; i < 10; i++)
    {
        for (auto lpMissile : *vMissiles)
        {
            if (lpMissile->GetIsFired() == false)
            {
                randAngle = (rand() % 168 - 18) * 100;
                lpMissile->SetType(Missile::SKILLTYPE::WormSKill_TYPE);
                lpMissile->SetIsFired(true);
                lpMissile->SetAngle(DegToRad(k)/** elapsedTime*1000*/);
                lpMissile->SetMoveSpeed(100);
                break;
            }
        }
        k -= 12;
        if (k == -330)
            break;
    }
}


