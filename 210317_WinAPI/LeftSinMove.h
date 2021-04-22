#pragma once
#include "MoveInterface.h"

class LeftSinMove : public MoveInterface
{
private:
	int dir;
public:
	virtual void DoMove(FPOINT* pos, float* angle);
	virtual void Renew();
	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };

	LeftSinMove() { dir = 1; }
};

