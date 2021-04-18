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
		if (fireInterface)
			delete fireInterface;
		fireInterface = changeFire;
	}

	virtual void DoFire(vector<Missile*>* vMissiles)
	{
		if (fireInterface)
			fireInterface->DoFire(vMissiles);
	}

	FireManager() : fireInterface(nullptr) {};
	~FireManager() { if (fireInterface) delete fireInterface; fireInterface = nullptr; };
};
