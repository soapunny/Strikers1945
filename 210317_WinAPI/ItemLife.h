#pragma once
#include "GameNode.h"
#include "Item.h"
class ItemLife :
    public Item
{
private:
	FPOINT ItemPos;
	vector<MoveInterface*> vMoveInterfaces;		
	MoveInterface* currMoveInterface;	
	float moveSpeed;
	float angle;
	int size;
	
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
	void RRRR();
};

