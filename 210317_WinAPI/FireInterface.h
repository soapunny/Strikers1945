#pragma once
#include "config.h"
#include "Missile.h"
#include <vector>

class FireInterface
{
protected:

public:
	virtual void DoFire(vector<Missile*>* vMissiles) = 0;
};

