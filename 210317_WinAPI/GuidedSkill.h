#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class GuidedSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	inline virtual void Renew() { time = 0.0f; }
};

