#pragma once
#include "SkillInterface.h"

class FireworkSkill :  public SkillInterface
{
private:
	bool isSkillReady;

public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	inline virtual void Renew() {time = 0.0f; isSkillReady = false;}

	FireworkSkill() { time = 0.0f; isSkillReady = false; }
};

