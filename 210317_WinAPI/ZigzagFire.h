#pragma once
#include "FireInterface.h"
class ZigzagFire :public FireInterface
{
	virtual void DoFire(vector<Missile*>* vMissiles);
};

