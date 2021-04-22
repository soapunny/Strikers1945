#pragma once
#include "MoveInterface.h"

class PointMove : public MoveInterface
{
private:
	int point[6][2] = { {WINSIZE_X / 8, WINSIZE_Y / 10}, {WINSIZE_X / 8 + 50, 3 * (WINSIZE_Y / 10)}, 
						{6 * (WINSIZE_X / 8), 2 * (WINSIZE_Y / 10)}, {7 * (WINSIZE_X / 8) - 50, 4 * (WINSIZE_Y / 10)}, 
						{3 * (WINSIZE_X / 8), (WINSIZE_Y / 10)}, {4 * (WINSIZE_X / 8), 4 * (WINSIZE_Y / 10)} };
	//int index = 0; 

public:
	virtual void DoMove(FPOINT* pos, float* angle);

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
};
