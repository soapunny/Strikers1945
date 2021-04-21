#pragma once
#include "config.h"
class ItemObserver
{
public:
	virtual void SetDropNotify(DROPENEMY dropItem) = 0;
	virtual void SetDropPos(FPOINT pos) = 0;
	virtual void SetIsItem(bool IsItemIsDrop) = 0;
};	