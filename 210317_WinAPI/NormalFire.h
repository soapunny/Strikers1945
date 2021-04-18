#pragma once
#include "FireInterface.h"

class NormalFire : public FireInterface
{
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};

