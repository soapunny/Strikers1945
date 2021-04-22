#pragma once
#include "MoveInterface.h"
class ZigzagMove: public MoveInterface
{
private:

public:
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
	virtual void Renew();
};

