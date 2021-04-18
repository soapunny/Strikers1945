#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class CircularSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile);
};
