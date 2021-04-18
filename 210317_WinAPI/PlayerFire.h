#pragma once
#include "FireInterface.h"

class PlayerFire : public FireInterface
{
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};

