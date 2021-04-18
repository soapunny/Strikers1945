#pragma once
#include "config.h"

class MoveInterface
{
protected:
	float moveSpeed;
	float time;

public:
	virtual void DoMove(FPOINT* pos, float* angle) = 0;

	virtual inline void SetMoveSpeed(float moveSpeed) = 0;
	virtual void Renew()=0;
};

