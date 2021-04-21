#pragma once
#include "ItemManager.h"
class ItemSubject
{
public:
	virtual void RegisterObserver(ItemManager* itemManager) = 0;
	virtual void ItemUnRegisterObserver() = 0;
	virtual void ItemnotifyObserve() = 0;
};
