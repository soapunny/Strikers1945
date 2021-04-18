#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class NormalSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile);
};

