#pragma once
#include "config.h"
#include "Missile.h"
#include <vector>

class FireInterface
{
protected:
	float time;
public:
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos) = 0;
	virtual void Renew() = 0;
};

