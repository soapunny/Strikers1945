#pragma once
#include "FireInterface.h"
class FireworkFire : public FireInterface
{
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos);
	virtual void Renew() { time = 0.0f; };
};

