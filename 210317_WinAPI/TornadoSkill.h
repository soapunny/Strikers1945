#pragma once
#include "SkillInterface.h"
class TornadoSkill :public SkillInterface
{
private:
	
public:
	virtual void UseSkill(Missile* missile, FPOINT* lpTargetPos);
	virtual void Renew() { time = 0.0f; };
};

