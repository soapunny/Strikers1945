#pragma once
#include "GameNode.h"
#include "Item.h"

class Image;
class ItemLife :
    public Item
{
private:

	
public:
	virtual HRESULT Init() { return S_OK; };
	virtual HRESULT Init(CollisionCheck* collisionCheck);
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();	
	void RRRR();
};

