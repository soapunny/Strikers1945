#pragma once
#include "config.h"
#include "MoveInterface.h"

class MoveManager	//���� <- �߰� ���
{
private:
	MoveInterface* moveInterface;
public:
	void ChangeMove(MoveInterface* changeMove)
	{
		if (moveInterface)
			delete moveInterface;
		moveInterface = changeMove;
	}

	void DoMove(FPOINT *pos, float* angle)
	{
		if (moveInterface)
			moveInterface->DoMove(pos, angle);
	}

	void SetMoveSpeed(float moveSpeed)
	{
		if (moveInterface)
			moveInterface->SetMoveSpeed(moveSpeed);
	}

	MoveManager() : moveInterface(nullptr) {};
	~MoveManager() { if (moveInterface) delete moveInterface; moveInterface = nullptr; };
};