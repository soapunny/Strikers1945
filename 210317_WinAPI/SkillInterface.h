#pragma once
#include "config.h"

class Missile;
class SkillInterface
{
public:
	virtual void UseSkill(Missile* missle) = 0;
};

