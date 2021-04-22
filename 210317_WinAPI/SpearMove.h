#pragma once
#include "MoveInterface.h"

class SpearMove :public MoveInterface
{
private:
	FPOINT* lpPlayerPos;
	int dir;
	RECT limitRect;

public:
	virtual void DoMove(FPOINT* pos, float* angle);
	virtual void Renew();

	virtual inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; };
	inline void SetLpPlayerPos(FPOINT* lpPlayerPos) { if(lpPlayerPos)this->lpPlayerPos = lpPlayerPos; };
	SpearMove() { time = 0.0f; dir = 1; limitRect.top = WINSIZE_Y / 6; limitRect.bottom = WINSIZE_Y * 5 / 6;  limitRect.left = WINSIZE_X / 6; limitRect.right = WINSIZE_X * 5 / 6; }
};

