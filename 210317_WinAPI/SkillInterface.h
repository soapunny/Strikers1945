#pragma once
#include "config.h"

class SkillInterface
{
public:
	virtual void UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime) = 0;
};

