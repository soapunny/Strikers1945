#pragma once
#include "MoveInterface.h"
class ComeAndGoMove : public MoveInterface
{
private:
	int randAngle = 0;
	bool LeftMove = true;
public:
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};