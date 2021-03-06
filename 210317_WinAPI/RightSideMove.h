#pragma once
#include "MoveInterface.h"
class RightSideMove : public MoveInterface
{
public:
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};

