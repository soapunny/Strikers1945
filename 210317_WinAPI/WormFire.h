#pragma once
#include "FireInterface.h"
class WormFire :	public FireInterface
{
private:
	int currTime = 0;
	int randAngle;
	int k=0;
public:
	virtual void DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};
