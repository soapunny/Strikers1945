#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class PlayerSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};
