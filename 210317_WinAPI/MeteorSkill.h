#pragma once
#include "SkillInterface.h"


class MeteorSkill :	public SkillInterface
{
	int currTime = 0;

	virtual void UseSkill(Missile* missile);
};