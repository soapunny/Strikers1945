#pragma once
#include "FireInterface.h"
class ZigzagFire :public FireInterface
{
	virtual void DoFire(vector<Missile*>* vMissiles);
	int a = 0;
};

