#pragma once
#include "config.h"
#include "FireInterface.h"
#include "Missile.h"

class FireManager
{
private:
	FireInterface* fireInterface;

public:
	void ChangeMove(FireInterface* changeFire)
	{
		if (fireInterface)
			delete fireInterface;
		fireInterface = changeFire;
	}

	void DoFire(vector<Missile*>* vMissiles)
	{
		if (fireInterface)
			fireInterface->DoFire(vMissiles);
	}

	FireManager() : fireInterface(nullptr) {};
	~FireManager() { if (fireInterface) delete fireInterface; fireInterface = nullptr; };
};
