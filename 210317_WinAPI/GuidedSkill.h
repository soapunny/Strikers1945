#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class GuidedSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile);
};

