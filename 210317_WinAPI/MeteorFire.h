#pragma once
#include "FireInterface.h"
class MeteorFire :	public FireInterface
{
private:
	int currTime = 0;
	int randAngle;
	int firedCount = 0;
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};
