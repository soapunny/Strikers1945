#pragma once
#include "FireInterface.h"

class GuidedFire : public FireInterface
{
private:
	float time = 0.0f;
public:
	virtual void DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* lpTargetPos);
	inline virtual void Renew() { time = 0.0f; }
};

