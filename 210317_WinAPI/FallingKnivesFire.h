#pragma once
#include "FireInterface.h"

class FallingKnivesFire : public FireInterface
{
public:
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* targetPos);
	inline virtual void Renew() { time = 0; }

	FallingKnivesFire() {};
	virtual ~FallingKnivesFire() {};
};