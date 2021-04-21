#pragma once
#include "config.h"
#include <vector>
#include "MoveManager.h"

class ItemManager;
class Item
{	
protected:
	MoveManager* moveManager;
	FPOINT dropPos;
	ItemManager* itemManager;
public:
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
};

