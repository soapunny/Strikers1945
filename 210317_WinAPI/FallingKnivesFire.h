#pragma once
#include "FireInterface.h"

class FallingKnivesFire: public FireInterface
{

public:
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	inline virtual void Renew() { time = 0; }
};

