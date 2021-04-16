#pragma once
#include "config.h"
#include "SkillInterface.h"

class SkillManager
{
private:
	SkillInterface* skillInterface;

public:
	void ChangeSkill(SkillInterface* changeSkill)
	{
		if (skillInterface)
			delete skillInterface;
		skillInterface = changeSkill;
	}

	void UseSkill(FPOINT* pos, float* angle, float moveSpeed, float moveTime)
	{
		if (skillInterface)
			skillInterface->UseSkill(pos, angle, moveSpeed, moveTime);
	}

	SkillManager() : skillInterface(nullptr) {};
	~SkillManager() { if (skillInterface) delete skillInterface; skillInterface = nullptr; };
};

