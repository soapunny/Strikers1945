#pragma once
#include "SkillInterface.h"
class NotSkill :
	public SkillInterface

{
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	inline virtual void Renew() { time = 0.0f; }
};

