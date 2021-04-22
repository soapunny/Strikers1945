#pragma once
#include "SkillInterface.h"
class ZigzagSkill : public SkillInterface
{
private: 

public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	inline virtual void Renew() { time = 0.0f; }
};

