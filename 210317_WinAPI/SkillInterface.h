#pragma once
#include "config.h"

class Missile;
class SkillInterface
{
protected:
	float time = 0.0f;
public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos) = 0;
	virtual void Renew() = 0;
};

