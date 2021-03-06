#pragma once
#include "MoveInterface.h"
class BackMove : public MoveInterface
{
	virtual void DoMove(FPOINT* pos, float* angle);
	virtual void Renew();

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};

