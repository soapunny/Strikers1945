#pragma once
#include "MoveInterface.h"
class RightDownMove :	public MoveInterface
{
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
	virtual void Renew() { time = 0.0f; }
};

