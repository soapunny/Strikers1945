#include "FireManager.h"
#include "FireInterface.h"

void FireManager::ChangeMove(FireInterface* changeFire)
{
	/*if (fireInterface)
		delete fireInterface;*/
	fireInterface = changeFire;
}

void FireManager::DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos)
{
	if (fireInterface)
		fireInterface->DoFire(collisionCheck, vMissiles, targetPos);
}

void FireManager::Renew()
{
	fireInterface->Renew();
}