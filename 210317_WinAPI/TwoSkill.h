#pragma once
#include "SkillInterface.h"
class TwoSkill :
	public SkillInterface
{
	int currTime = 0;


	virtual void UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime);
};

