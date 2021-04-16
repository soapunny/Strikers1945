#pragma once
#include "FireInterface.h"

class NormalFire : public FireInterface
{
private:

public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};

