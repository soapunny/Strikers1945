#pragma once
#include "SkillInterface.h"
class NotSkill :
	public SkillInterface

{
	int currTime = 0;


	virtual void UseSkill(Missile* missile);
};

