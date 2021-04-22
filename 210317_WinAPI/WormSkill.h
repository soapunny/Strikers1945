#pragma once
#include "SkillInterface.h"
class WormSkill :	public SkillInterface
{
	int currTime = 0;

	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; }
};
