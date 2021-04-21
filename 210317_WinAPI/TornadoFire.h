#pragma once
#include "FireInterface.h"
class TornadoFire :public FireInterface
{
private:
	int a = 0;
public:
	void DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};