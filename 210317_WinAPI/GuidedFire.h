#pragma once
#include "FireInterface.h"

class GuidedFire : public FireInterface
{
private:
	float time = 0.0f;
public:
	virtual void DoFire(vector<Missile*>* vMissiles);
};

