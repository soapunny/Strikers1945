#pragma once
#include "MoveInterface.h"
class PhaseChangeMove : public MoveInterface
{
private:
	int randAngle = 0;
	bool LeftMove = true;
	int phase = 1;
public:
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};
