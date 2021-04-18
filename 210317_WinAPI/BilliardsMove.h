#pragma once
#include "MoveInterface.h"

class BilliardsMove : public MoveInterface
{
private:
	int bossSize;
public:
	virtual void DoMove(FPOINT* pos, float* angle);
	virtual inline void Renew() { time = 0.0f; };

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
	BilliardsMove() { time = 0.0f; bossSize = 200; }
};

