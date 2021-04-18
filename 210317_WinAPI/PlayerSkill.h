#pragma once
#include "SkillInterface.h"
#include "Missile.h"

class PlayerSkill : public SkillInterface
{
public:
	virtual void UseSkill(Missile* missile);
};
