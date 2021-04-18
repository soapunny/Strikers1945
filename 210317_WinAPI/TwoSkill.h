#pragma once
#include "SkillInterface.h"
class TwoSkill :
	public SkillInterface
{

	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};

