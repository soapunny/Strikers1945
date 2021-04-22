#pragma once
#include "config.h"

class Missile;
class CollisionCheck;
class FireInterface
{
protected:
	float time;
	CollisionCheck* collisionCheck;

public:
	virtual void DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos) = 0;
	virtual void Renew() = 0;

	FireInterface() {}
	virtual ~FireInterface() {}
};

