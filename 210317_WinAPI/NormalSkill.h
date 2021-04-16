#pragma once
#include "SkillInterface.h"

class NormalSkill : public SkillInterface
{
public:
	virtual void UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime);
};

