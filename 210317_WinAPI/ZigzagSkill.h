#pragma once
#include "SkillInterface.h"
class ZigzagSkill : public SkillInterface
{
private: 
	float missileTimer=0;
public:
	virtual void UseSkill(Missile* missile);
};

