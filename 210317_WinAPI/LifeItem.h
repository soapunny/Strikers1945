#pragma once
#include "GameNode.h"
class LifeItem: public GameNode
{
private:
	int recoveryLife;
	Image* img;
	FPOINT pos;
	float moveSpeed;
	float moveTime;
	int size;
	RECT shape;
	float angle;
	bool isFired; 
public:
	inline void SetStartPos(FPOINT pos) { this->pos = pos; }
};

