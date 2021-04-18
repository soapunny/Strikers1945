#pragma once
#include "FireInterface.h"
class WormFire :	public FireInterface
{
private:
	int currTime = 0;
	int randAngle;
	int k=0;
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};
