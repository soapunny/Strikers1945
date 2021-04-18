#pragma once
#include "SkillInterface.h"
class WormSkill :	public SkillInterface
{
	int currTime = 0;

	virtual void UseSkill(Missile* missile);
};
