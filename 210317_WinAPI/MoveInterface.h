#pragma once
#include "config.h"

class MoveInterface
{
protected:
	float moveSpeed;

public:
	virtual void DoMove(FPOINT* pos, float* angle) = 0;

	virtual inline void SetMoveSpeed(float moveSpeed) = 0;
};

