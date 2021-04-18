#pragma once
#include "config.h"
#include "SkillInterface.h"
#include "Missile.h"

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

	void UseSkill(Missile* missile)
	{
		if (skillInterface)
			skillInterface->UseSkill(missile);
	}

	SkillManager() : skillInterface(nullptr) {};
	~SkillManager() { if (skillInterface) delete skillInterface; skillInterface = nullptr; };
};

