#pragma once
#include "SkillInterface.h"
class TornadoSkill :public SkillInterface
{
private:
	
public:
	virtual void UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime);
};

