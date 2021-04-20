#pragma once
#include "config.h"

class FireInterface;
class Missile;
class CollisionCheck;
class FireManager
{
private:
	FireInterface* fireInterface;

public:
	virtual	void ChangeMove(FireInterface* changeFire);

	void DoFire(CollisionCheck* collisionCheck, vector<Missile*>* vMissiles, FPOINT* targetPos);

	virtual void Renew();

	FireManager() : fireInterface(nullptr) {};
	~FireManager() { /*if (fireInterface) delete fireInterface; fireInterface = nullptr;*/ };
};
