#include "FireManager.h"
#include "FireInterface.h"

void FireManager::ChangeMove(FireInterface* changeFire)
{
	/*if (fireInterface)
		delete fireInterface;*/
	fireInterface = changeFire;
}

void FireManager::DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos)
{
	if (fireInterface)
		fireInterface->DoFire(vMissiles, targetPos);
}

void FireManager::Renew()
{
	fireInterface->Renew();
}