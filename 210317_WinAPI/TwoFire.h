#pragma once
#include "FireInterface.h"
class TwoFire :
	public FireInterface
{
private:
	int currTime = 0;
	int randAngle;
	int k = -100;
	bool isTwo = false;
public:
	virtual void DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};
