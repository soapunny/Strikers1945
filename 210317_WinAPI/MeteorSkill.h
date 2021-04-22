#pragma once
#include "SkillInterface.h"


class MeteorSkill :	public SkillInterface
{
	int currTime = 0;

	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	virtual void Renew() {time = 0.0f;}
};