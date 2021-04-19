#pragma once
#include "FireInterface.h"
class ZigzagFire :public FireInterface
{
private:
	int a = 0;
public:
	void DoFire(vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};

