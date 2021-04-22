#pragma once
#include "FireInterface.h"

class PlayerFire : public FireInterface
{
public:
	virtual void DoFire(CollisionCheck* collisionCheck,vector<Missile*>* vMissiles, FPOINT* targetPos);
	inline virtual void Renew() { time = 0.0f; }
};

