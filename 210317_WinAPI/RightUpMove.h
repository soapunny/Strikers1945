#pragma once
#include "MoveInterface.h"
class RightUpMove :	public MoveInterface
{
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};