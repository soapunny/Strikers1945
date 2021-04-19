#pragma once
#include "config.h"

class Missile;
class FireInterface
{
protected:
	float time;
public:
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos) = 0;
	virtual void Renew() = 0;

	FireInterface() {}
	virtual ~FireInterface() {}
};

