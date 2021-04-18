#pragma once
#include "config.h"
#include "FireInterface.h"
#include "Missile.h"

class FireManager
{
private:
	FireInterface* fireInterface;

public:
	virtual	void ChangeMove(FireInterface* changeFire)
	{
		/*if (fireInterface)
			delete fireInterface;*/
		fireInterface = changeFire;
	}

	void DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos)
	{
		if (fireInterface)
			fireInterface->DoFire(vMissiles, targetPos);
	}

	inline virtual void Renew() 
	{
		fireInterface->Renew();
	}

	FireManager() : fireInterface(nullptr) {};
	~FireManager() { /*if (fireInterface) delete fireInterface; fireInterface = nullptr;*/ };
};
