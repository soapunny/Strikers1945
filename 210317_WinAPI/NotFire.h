#pragma once
#include "FireInterface.h"
class NotFire :
	public FireInterface
{
private:
	int currTime = 0;
	int randAngle;
	int k = -100;
	bool isTwo = false;
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};
